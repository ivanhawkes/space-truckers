#include "Game/GameInstanceSpaceTrucker.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SaveGameSpaceTrucker.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "SpaceTruckers/Public/Universe/SolarSystem.h"


void UGameInstanceSpaceTrucker::Init()
{
	Super::Init();

	// Bind to the global delegate that triggers right after a world finishes BeginPlay
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UGameInstanceSpaceTrucker::OnWorldInitialized);
}


void UGameInstanceSpaceTrucker::Shutdown()
{
	// Always unbind to prevent dangling pointer references when the game shuts down
	FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);

	Super::Shutdown();
}


void UGameInstanceSpaceTrucker::OnWorldInitialized(UWorld* newWorld, const UWorld::InitializationValues IVS)
{
	if (!newWorld)
		return;

	// Filter out non-game worlds (Editor, Preview Windows, etc.)
	if (newWorld->WorldType == EWorldType::Game || newWorld->WorldType == EWorldType::PIE)
	{
		// Retrieve the map name to perform level-specific logic
		FString LevelName = newWorld->GetMapName();

		UE_LOG(LogTemp, Log, TEXT("Game Instance detected BeginPlay for level: %s"), *LevelName);

		// There should only be one universe actor in a level so we can just ask for it.
		if (shouldGenerate)
			GenerateNewUniverse(newWorld);
		shouldGenerate = false;

		// Dynamic actors must be explicitly loaded.
		if (shouldLoadUniverse)
			LoadDynamicActors();
		shouldLoadUniverse = false;
	}
}


void UGameInstanceSpaceTrucker::NewLevelFromTemplate(
	const UObject* WorldContextObject,
	const TSoftObjectPtr<UWorld> Level,
	int64 randomSeed,
	UDataTable* SolarSystemNames,
	UDataTable* PlanetNames)
{
	const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(Level.ToString()));

	// Keep a copy of the generation parameters.
	universeParameters.randomSeed = randomSeed;
	universeParameters.planetNames = PlanetNames;
	universeParameters.solarSystemNames = SolarSystemNames;

	// Load the level and start playback.
	UGameplayStatics::OpenLevel(WorldContextObject, LevelName, true);

	// Indicate the solar system needs to be generated now.
	shouldGenerate = true;
}


void UGameInstanceSpaceTrucker::GenerateNewUniverse(UWorld* newWorld)
{
	constexpr double pi{3.14159265358979323846};
	constexpr double toRadians{pi / 180.0f};

	// Apply the seed for the randomness of this universe using the Unix
	// timestamp as a seed.
	FRandomStream randomStream;
	randomStream.Initialize(universeParameters.randomSeed);

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow,
	                                 FString::Format(
		                                 TEXT("Generate new universe using seed: {0}"), {
			                                 universeParameters.randomSeed
		                                 })
	                                 , true);

	if (universeParameters.solarSystemNames)
	{
		static const FString ContextString(TEXT("Finding Row in solar system table"));

		TArray<FName> rows = universeParameters.solarSystemNames->GetRowNames();

		// Randomise the array by swapping elements multiple times. This is probably not
		// very optimal, but it will do for now.
		for (int i = 0; i < rows.Max() * 3; i++)
		{
			const int32 firstRow = randomStream.RandRange(0, rows.Max() - 1);
			const int32 secondRow = randomStream.RandRange(0, rows.Max() - 1);
			std::swap(rows[firstRow], rows[secondRow]);
		}

		float rotationDegree{0.0f};
		float expansionOutward{0.0f};

		// Generate a set of solar systems.
		for (int i = 0; i < 200; i++)
		{
			// Calculate some random offsets. Allowing the offset to be positive or negative.
			float randomOutward{0.0f};
			if (universeParameters.randomExpansionOutward > 0.0f)
			{
				randomOutward = randomStream.FRandRange(-universeParameters.randomExpansionOutward,
				                                        universeParameters.randomExpansionOutward);
			}
			float randomRotation{0.0f};
			if (universeParameters.randomRotationDegree > 0.0f)
			{
				randomRotation = randomStream.FRandRange(-universeParameters.randomRotationDegree,
				                                         universeParameters.randomRotationDegree);
			}

			// Centre of the universe is based on the universe actor location.
			FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
			FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

			// Give the new solar system an offset from the universe.
			const float distance = universeParameters.deadZone + expansionOutward + randomOutward;
			const float x = sin((rotationDegree + randomRotation) * toRadians) * distance;
			const float y = cos((rotationDegree + randomRotation) * toRadians) * distance;
			SpawnLocation.X += x;
			SpawnLocation.Y += y;

			// Update the rotation and expansion outwards.
			expansionOutward += universeParameters.fixedExpansionOutward;
			rotationDegree += universeParameters.fixedRotationDegree;

			auto& row = rows[i];

			FActorSpawnParameters spawnParameters;
			spawnParameters.Name = row;
			spawnParameters.bHideFromSceneOutliner = false;
			spawnParameters.ObjectFlags |= RF_Transient;
			spawnParameters.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
			ASolarSystemActor* solarSystemActor = newWorld->SpawnActor<ASolarSystemActor>(
				SpawnLocation, SpawnRotation, spawnParameters);

			// Set the name for this actor.
			solarSystemActor->solarSystemName = row.ToString();

			// Scale the suns by 0.1 to 50.0.
			const float scale = static_cast<float>(randomStream.RandRange(1, 50)) / 10.0f;
			solarSystemActor->sunScale = FVector(scale, scale, scale);

			// Keep a reference to the actors.
			solarSystemShadowList.Add(solarSystemActor);

#if WITH_EDITOR
			// Set a label for the outliner and make our new actor a child of the universe.
			solarSystemActor->SetActorLabel(row.ToString());
#endif
		}
	}
}


void UGameInstanceSpaceTrucker::SaveLevelAndPlayerState(FString SlotName)
{
	USaveGameSpaceTrucker* saveGame = Cast<USaveGameSpaceTrucker>(
		UGameplayStatics::CreateSaveGameObject(USaveGameSpaceTrucker::StaticClass()));
	if (!saveGame) return;

	// HACK: Need a way to set this properly.
	saveGame->lastMapName = "L_TemplateEmpty";

	// Get the player location.
	if (ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		saveGame->playerLocation = PlayerChar->GetActorLocation();
	}

	// Dynamic actors must be explicitly saved.
	SaveDynamicActors(saveGame);

	// Write everything to the disk slot.
	UGameplayStatics::SaveGameToSlot(saveGame, SlotName, 0);
}


void UGameInstanceSpaceTrucker::LoadLevelAndPlayerState(FString SlotName)
{
	// Open the saved map.
	UGameplayStatics::OpenLevel(GetWorld(), FName("L_TemplateEmpty"));

	// Indicate we need to load the universe saved data.
	shouldLoadUniverse = true;
}


void UGameInstanceSpaceTrucker::ClearCurrentDynamicActors()
{
	// Delete all the actors in the list.
	for (const auto actor : solarSystemShadowList)
	{
		if (actor)
			actor->Destroy();
	}

	solarSystemShadowList.Empty();
}


void UGameInstanceSpaceTrucker::SaveActor(USaveGameSpaceTrucker* saveGame, const TObjectPtr<AActor> actor)
{
	FActorSaveData actorData;
	actorData.actorClass = actor->GetClass();
	actorData.transform = actor->GetActorTransform();
	actorData.name = actor->GetName();

	// Serialise variables flagged with 'SaveGame'
	FMemoryWriter MemoryWriter(actorData.serializedData);
	FObjectAndNameAsStringProxyArchive archive(MemoryWriter, true);
	archive.ArIsSaveGame = true;
	actor->Serialize(archive);

	// Add them to the list.
	saveGame->SavedDynamicActors.Add(actorData);
}


void UGameInstanceSpaceTrucker::SaveDynamicActors(USaveGameSpaceTrucker* saveGame)
{
	// Save all the actors in the list.
	for (const auto actor : solarSystemShadowList)
	{
		if (actor)
			SaveActor(saveGame, actor);
	}
}


void UGameInstanceSpaceTrucker::LoadDynamicActors()
{
	// Remove the current dynamic actors to prevent duplication.
	ClearCurrentDynamicActors();

	// Ensure the save file exists.
	if (!UGameplayStatics::DoesSaveGameExist("Save01", 0)) return;

	// Load the data and cast it.
	if (USaveGameSpaceTrucker* saveGame = Cast<USaveGameSpaceTrucker>(UGameplayStatics::LoadGameFromSlot("Save01", 0)))
	{
		for (const FActorSaveData& actorData : saveGame->SavedDynamicActors)
		{
			// Check it even though it should never fail.
			if (actorData.actorClass)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				//SpawnParams.TransformScaleMethod = actorData.;
		
				// Instantiate the actor into the active Level.
				if (AActor* newActor = GetWorld()->SpawnActor<AActor>(actorData.actorClass, actorData.transform,
				                                                      SpawnParams))
				{
					// Track any spawned actors in our list.
					solarSystemShadowList.Add(newActor);

					// Hydrate the newly spawned actor.
					FMemoryReader memoryReader(actorData.serializedData);
					FObjectAndNameAsStringProxyArchive Archive(memoryReader, true);
					Archive.ArIsSaveGame = true;
					newActor->Serialize(Archive);
					
#if WITH_EDITOR
					// Set a label for the outliner and make our new actor a child of the universe.
					newActor->SetActorLabel(actorData.name);
#endif
				}
			}
		}
	}
}
