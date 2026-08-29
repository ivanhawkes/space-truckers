#include "Game/GameInstanceSpaceTrucker.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SaveGameSpaceTrucker.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Universe/SolarSystem.h"
#include "Universe/Planet.h"
#include "Universe/Satellite.h"
#include "Universe/Universe.h"


UGameInstanceSpaceTrucker::UGameInstanceSpaceTrucker()
{
}


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


void UGameInstanceSpaceTrucker::Tick(float DeltaTime)
{
	// Ensure we don't tick inside CDO (Class Default Object)
	if (HasAnyFlags(RF_ClassDefaultObject)) return;

	gameplaySeconds += DeltaTime * timeMultiplier;
}


ETickableTickType UGameInstanceSpaceTrucker::GetTickableTickType() const
{
	// Avoid ticking the Class Default Object.
	return HasAnyFlags(RF_ClassDefaultObject) ? ETickableTickType::Never : ETickableTickType::Always;
}


bool UGameInstanceSpaceTrucker::IsTickable() const
{
	// Returns true if the object is fully initialised and allowed to tick.
	return !HasAnyFlags(RF_ClassDefaultObject);
}


TStatId UGameInstanceSpaceTrucker::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMyGameInstance, STATGROUP_Tickables);
}


void UGameInstanceSpaceTrucker::LoadUniverse()
{
	if (shouldLoadUniverse)
	{
		// Ensure the save file exists.
		if (!UGameplayStatics::DoesSaveGameExist(slotName, 0)) return;

		// Load the data and cast it.
		if (USaveGameSpaceTrucker* saveGame = Cast<USaveGameSpaceTrucker>(
			UGameplayStatics::LoadGameFromSlot(slotName, 0)))
		{
			// Retrieve all the useful information we saved.
			gameplaySeconds = saveGame->gameplaySeconds;
			timeMultiplier = saveGame->timeMultiplier;

			LoadDynamicActors(saveGame);
		}
	}

	shouldLoadUniverse = false;
}


void UGameInstanceSpaceTrucker::OnWorldInitialized(UWorld* NewWorld, const UWorld::InitializationValues IVS)
{
	if (!NewWorld)
		return;

	// Filter out non-game worlds (Editor, Preview Windows, etc.)
	if (NewWorld->WorldType == EWorldType::Game || NewWorld->WorldType == EWorldType::PIE)
	{
		// Only generate the universe if the flag is set. Only do it once.
		if (shouldGenerate)
			GenerateNewUniverse(NewWorld);
		shouldGenerate = false;

		// Dynamic actors must be explicitly loaded.
		LoadUniverse();
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

	// Reset the gameplay clock.
	gameplaySeconds = 0.0f;
}


void UGameInstanceSpaceTrucker::CreateSolarSystems(UWorld* NewWorld, FRandomStream RandomStream,
                                                   const TArray<FName>& SolarSystemNameList,
                                                   const TArray<FName>& PlanetNameList)
{
	double rotationDegree{0.0f};
	double expansionOutward{0.0f};

	// Give the entire universe a spin direction.
	double galacticAxialRotation = RandomStream.FRandRange(-1.0f, 1.0f);
	if (galacticAxialRotation <= 0)
		galacticAxialRotation = -1.0f;
	else
		galacticAxialRotation = 1.0f;

	// Generate a set of solar systems.
	for (int i = 0; i < universeParameters.numberOfSolarSystems; i++)
	{
		// Calculate some random offsets. Allowing the offset to be positive or negative.
		double randomOutward{0.0f};
		randomOutward = RandomStream.FRandRange(-solarSystemOrbit.randomExpansionOutward,
		                                        solarSystemOrbit.randomExpansionOutward);

		// The random rotation is an offset from the fixed rotation.  
		double randomRotation{0.0f};
		randomRotation = RandomStream.FRandRange(-solarSystemOrbit.randomRotationDegree,
		                                         solarSystemOrbit.randomRotationDegree);

		// Centre of the universe is based on the universe actor location.
		FVector spawnLocation = FVector(0.0f, 0.0f, 0.0f);
		const double pitch = RandomStream.FRandRange(0, 30.0);
		const double yaw = RandomStream.FRandRange(0, 30.0);
		const double roll = RandomStream.FRandRange(0, 30.0);
		FRotator spawnRotation = FRotator(pitch, yaw, roll);

		// Give the new solar system an offset from the universe.
		const double distance = solarSystemOrbit.deadZone + expansionOutward + randomOutward;
		const double x = sin((rotationDegree + randomRotation) * Universe::toRadians) * distance;
		const double y = cos((rotationDegree + randomRotation) * Universe::toRadians) * distance;
		spawnLocation.X += x;
		spawnLocation.Y += y;

		// Update the rotation and expansion outwards.
		expansionOutward += solarSystemOrbit.fixedExpansionOutward;
		rotationDegree += solarSystemOrbit.fixedRotationDegree * galacticAxialRotation;

		auto& row = SolarSystemNameList[i];

		FActorSpawnParameters spawnParameters;
		spawnParameters.Name = row;
		spawnParameters.bHideFromSceneOutliner = false;
		spawnParameters.ObjectFlags |= RF_Transient;
		spawnParameters.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto actor = NewWorld->SpawnActor<ASolarSystemActor>(bpSolarSystem,
		                                                     spawnLocation, spawnRotation, spawnParameters);

		// Tag the actor in case we need to find it later.
		actor->Tags.Add(FName("DynamicSpawn"));

		// Set the name for this actor.
		actor->solarSystemName = row.ToString();
		actor->axialRotation = RandomStream.FRandRange(-0.05f, 0.05f);

		// Need to cast to the interface to access the callback.
		if (ISavableActorInterface* iSave = Cast<ISavableActorInterface>(actor))
		{
			iSave->OnPostInitialSpawn();
		}

#if WITH_EDITOR
		// Set a label for the outliner and make our new actor a child of the universe.
		actor->SetActorLabel(row.ToString());
#endif

		// Let's make some planets.
		CreatePlanets(NewWorld, RandomStream, actor, PlanetNameList);
	}
}


void UGameInstanceSpaceTrucker::CreatePlanets(UWorld* NewWorld, FRandomStream RandomStream,
                                              const TObjectPtr<ASolarSystemActor> OrbitParent,
                                              const TArray<FName>& PlanetNameList)
{
	double expansionOutward{0.0f};

	// Generate a set of planets.
	const int32 numberOfPlanets = RandomStream.RandRange(universeParameters.minNumberOfPlanets,
	                                                     universeParameters.maxNumberOfPlanets);
	for (int i = 0; i < numberOfPlanets; i++)
	{
		double coinToss = RandomStream.FRandRange(0.0f, 1.0f);
		double flipSpin {1.0f};
		if (coinToss < 0.2f)
			flipSpin = -1.0f;

		// Calculate some random offsets. Allowing the offset to be positive or negative.
		double randomOutward{0.0f};
		randomOutward = RandomStream.FRandRange(-planetOrbit.randomExpansionOutward,
		                                        planetOrbit.randomExpansionOutward);
		const double randomRotation{
			RandomStream.FRandRange(-180.0f,
			                        180.0f)
		};

		// Centre of the universe is based on the universe actor location.
		FVector spawnLocation = OrbitParent->GetActorLocation();
		const double pitch = RandomStream.FRandRange(0, 30.0);
		const double yaw = RandomStream.FRandRange(0, 30.0);
		const double roll = RandomStream.FRandRange(0, 30.0);
		FRotator spawnRotation = FRotator(pitch, yaw, roll);

		// Give the new solar system an offset from the sun.
		const double distance = planetOrbit.deadZone + expansionOutward + randomOutward;
		const double x = sin((randomRotation) * Universe::toRadians) * distance;
		const double y = cos((randomRotation) * Universe::toRadians) * distance;
		spawnLocation.X += x;
		spawnLocation.Y += y;

		// Update the rotation and expansion outwards.
		expansionOutward += planetOrbit.fixedExpansionOutward;

		auto& row = PlanetNameList[++planetNameIndex];

		FActorSpawnParameters spawnParameters;
		spawnParameters.Name = row;
		spawnParameters.bHideFromSceneOutliner = false;
		spawnParameters.ObjectFlags |= RF_Transient;
		spawnParameters.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto actor = NewWorld->SpawnActor<APlanetActor>(bpPlanet,
		                                                spawnLocation, spawnRotation, spawnParameters);

		// Tag the actor in case we need to find it later.
		actor->Tags.Add(FName("DynamicSpawn"));

		// Set the members.
		actor->planetName = row.ToString();
		actor->orbitParent = OrbitParent;
		actor->orbitRotation = randomRotation;
		actor->orbitRadius = distance;

		// TODO: The spin velocity limits need to be configurable.
		actor->axialRotation = RandomStream.FRandRange(0.001f, 0.05f) * OrbitParent->SpinDirection() * flipSpin;

		// Need to cast to the interface to access the callback.
		if (ISavableActorInterface* iSave = Cast<ISavableActorInterface>(actor))
		{
			iSave->OnPostInitialSpawn();
		}

#if WITH_EDITOR
		// Set a label for the outliner and make our new actor a child of the universe.
		actor->SetActorLabel(row.ToString());
#endif

		// Let's make some satellites.
		CreateSatellites(NewWorld, RandomStream, actor, PlanetNameList);
	}
}


void UGameInstanceSpaceTrucker::CreateSatellites(UWorld* NewWorld, FRandomStream RandomStream,
                                                 const TObjectPtr<APlanetActor> OrbitParent,
                                                 const TArray<FName>& PlanetNameList)
{
	double rotationDegree{0.0f};
	double expansionOutward{0.0f};

	// Generate a set of planets.
	const int32 numberOfPlanets = RandomStream.RandRange(universeParameters.minNumberOfSatellites,
	                                                     universeParameters.maxNumberOfSatellites);
	for (int i = 0; i < numberOfPlanets; i++)
	{
		// Calculate some random offsets. Allowing the offset to be positive or negative.
		double randomOutward{0.0f};
		randomOutward = RandomStream.FRandRange(-satelliteOrbit.randomExpansionOutward,
		                                        satelliteOrbit.randomExpansionOutward);
		const double randomRotation{
			RandomStream.FRandRange(-180.0f,
			                        180.0f)
		};

		// Centre of the universe is based on the universe actor location.
		FVector spawnLocation = OrbitParent->GetActorLocation();
		const double pitch = RandomStream.FRandRange(0, 30.0);
		const double yaw = RandomStream.FRandRange(0, 30.0);
		const double roll = RandomStream.FRandRange(0, 30.0);
		FRotator spawnRotation = FRotator(pitch, yaw, roll);

		// Give the new solar system an offset from the sun.
		const double distance = satelliteOrbit.deadZone + expansionOutward + randomOutward;
		const double x = sin((rotationDegree + randomRotation) * Universe::toRadians) * distance;
		const double y = cos((rotationDegree + randomRotation) * Universe::toRadians) * distance;
		spawnLocation.X += x;
		spawnLocation.Y += y;

		// Update the rotation and expansion outwards.
		expansionOutward += satelliteOrbit.fixedExpansionOutward;
		rotationDegree += satelliteOrbit.fixedRotationDegree;

		// TODO: Make a set of names just for satellites.
		auto& row = PlanetNameList[++satelliteNameIndex];
		const FName satelliteName = FName(OrbitParent->planetName + "-" + row.ToString());

		FActorSpawnParameters spawnParameters;
		spawnParameters.Name = satelliteName;
		spawnParameters.bHideFromSceneOutliner = false;
		spawnParameters.ObjectFlags |= RF_Transient;
		spawnParameters.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto actor = NewWorld->SpawnActor<ASatelliteActor>(bpSatellite,
		                                                   spawnLocation, spawnRotation, spawnParameters);

		// Tag the actor in case we need to find it later.
		actor->Tags.Add(FName("DynamicSpawn"));

		// Set the members.
		actor->satelliteName = satelliteName.ToString();
		actor->orbitParent = OrbitParent;
		actor->orbitRotation = randomRotation;
		actor->orbitRadius = distance;

		// TODO: The spin velocity limits need to be configurable.
		actor->axialRotation = RandomStream.FRandRange(0.001f, 0.05f) * OrbitParent->orbitParent->SpinDirection();

		// Need to cast to the interface to access the callback.
		if (ISavableActorInterface* iSave = Cast<ISavableActorInterface>(actor))
		{
			iSave->OnPostInitialSpawn();
		}

#if WITH_EDITOR
		// Set a label for the outliner and make our new actor a child of the universe.
		actor->SetActorLabel(row.ToString());
#endif
	}
}


void UGameInstanceSpaceTrucker::GenerateNewUniverse(UWorld* NewWorld)
{
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

	// Make sure we have a list of names which are suitable for solar systems.
	if (universeParameters.solarSystemNames && universeParameters.planetNames)
	{
		TArray<FName> solarSystemNameList = universeParameters.solarSystemNames->GetRowNames();

		// Randomise the array by swapping elements multiple times. This is probably not
		// very optimal, but it will do for now.
		for (int i = 0; i < solarSystemNameList.Max() * 3; i++)
		{
			const int32 firstRow = randomStream.RandRange(0, solarSystemNameList.Max() - 1);
			const int32 secondRow = randomStream.RandRange(0, solarSystemNameList.Max() - 1);
			std::swap(solarSystemNameList[firstRow], solarSystemNameList[secondRow]);
		}

		TArray<FName> planetNameList = universeParameters.planetNames->GetRowNames();

		// Randomise the array by swapping elements multiple times. This is probably not
		// very optimal, but it will do for now.
		for (int i = 0; i < planetNameList.Max() * 3; i++)
		{
			const int32 firstRow = randomStream.RandRange(0, planetNameList.Max() - 1);
			const int32 secondRow = randomStream.RandRange(0, planetNameList.Max() - 1);
			std::swap(planetNameList[firstRow], planetNameList[secondRow]);
		}

		// Create a set of solar system actors.
		CreateSolarSystems(NewWorld, randomStream, solarSystemNameList, planetNameList);
	}
}


void UGameInstanceSpaceTrucker::SaveLevelAndPlayerState(FString SlotName)
{
	USaveGameSpaceTrucker* saveGame = Cast<USaveGameSpaceTrucker>(
		UGameplayStatics::CreateSaveGameObject(USaveGameSpaceTrucker::StaticClass()));
	if (!saveGame) return;

	// HACK: Need a way to set this properly.
	saveGame->lastMapName = "L_TemplateEmpty";

	// Handle any useful game instance data.
	saveGame->gameplaySeconds = gameplaySeconds;
	saveGame->timeMultiplier = timeMultiplier;

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
	// HACK: TODO: We need to get this from anyone other than a hard-coded value.
	UGameplayStatics::OpenLevel(GetWorld(), FName("L_TemplateEmpty"));

	// Indicate we need to load the universe saved data.
	shouldLoadUniverse = true;
	slotName = SlotName;
}


void UGameInstanceSpaceTrucker::ClearCurrentDynamicActors()
{
	if (!GetWorld()) return;

	TArray<AActor*> deleteList;
	for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag(FName("DynamicSpawn")))
		{
			deleteList.Add(*it);
		}
	}

	// Delete all the actors in the list.
	for (const auto actor : deleteList)
	{
		if (actor)
			actor->Destroy();
	}
}


void UGameInstanceSpaceTrucker::SaveDynamicActors(USaveGameSpaceTrucker* saveGame)
{
	// Save all the actors that have our tag.
	for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		auto actor = *it;

		if (actor->ActorHasTag(FName("DynamicSpawn")))
		{
			// Need to cast to the interface to access the callback.
			if (ISavableActorInterface* iSave = Cast<ISavableActorInterface>(actor))
			{
				FActorSaveData saveData;
				iSave->OnPreSave(saveData);

				// Push the saved actor data onto the save game instance.
				saveGame->savedDynamicActors.Add(saveData);

				// Save the components as well.
				SaveActorComponents(actor, saveData);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Saving dynamic actor without ISavableActorInterface"));
			}
		}
	}
}


void UGameInstanceSpaceTrucker::SaveActorComponents(AActor* TargetActor, FActorSaveData& SaveData)
{
	// Fetch all components attached to the Actor
	TInlineComponentArray<UActorComponent*> Components(TargetActor);
	for (UActorComponent* component : Components)
	{
		// Ignore default compiler components (only process dynamically spawned ones)
		if (!component || component->IsCreatedByConstructionScript() || component->HasAnyFlags(RF_DefaultSubObject))
		{
			continue;
		}

		FComponentSaveData componentSaveData;
		componentSaveData.componentClass = component->GetClass();
		componentSaveData.name = FName(component->GetName());

		// Set up the memory writers for binary serialization
		FMemoryWriter MemoryWriter(componentSaveData.serializedData);
		FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, false);
		Archive.ArIsSaveGame = true; // Targets properties marked UPROPERTY(SaveGame)

		// Serialize variables flagged with UPROPERTY(SaveGame) inside the component
		component->Serialize(Archive);

		SaveData.dynamicComponents.Add(componentSaveData);
	}
}


void UGameInstanceSpaceTrucker::LoadDynamicActors(USaveGameSpaceTrucker* saveGame)
{
	// Remove the current dynamic actors to prevent duplication.
	ClearCurrentDynamicActors();

	for (FActorSaveData& saveData : saveGame->savedDynamicActors)
	{
		// Check it even though it should never fail.
		if (saveData.actorClass)
		{
			FActorSpawnParameters spawnParameters;
			spawnParameters.Name = saveData.name;
			spawnParameters.bHideFromSceneOutliner = false;
			spawnParameters.ObjectFlags |= RF_Transient;
			spawnParameters.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
			spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Instantiate the actor into the active Level.
			auto actor = GetWorld()->SpawnActor<AActor>(saveData.actorClass,
			                                            saveData.location, saveData.rotation,
			                                            spawnParameters);
			if (actor)
			{
				// Tag the actor in case we need to find it later.
				actor->Tags.Add(FName("DynamicSpawn"));

				// Need to cast to the interface to access the callback.
				if (ISavableActorInterface* iSave = Cast<ISavableActorInterface>(actor))
				{
					iSave->OnPostLoad(saveData);
					LoadActorComponents(actor, saveData);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Loading dynamic actor without ISavableActorInterface"));
				}
			}
		}
	}
}


void UGameInstanceSpaceTrucker::LoadActorComponents(AActor* TargetActor, FActorSaveData& SaveData)
{
	// Clean up existing dynamic components first to avoid duplication.
	TInlineComponentArray<UActorComponent*> existing(TargetActor);
	for (UActorComponent* component : existing)
	{
		if (component && !component->HasAnyFlags(RF_DefaultSubObject) && !component->IsCreatedByConstructionScript())
		{
			component->DestroyComponent();
		}
	}

	for (const FComponentSaveData& componentSaveData : SaveData.dynamicComponents)
	{
		if (!componentSaveData.componentClass) continue;

		// Re-create the component.
		UActorComponent* newComponent = NewObject<UActorComponent>(
			TargetActor,
			componentSaveData.componentClass,
			componentSaveData.name
		);

		if (newComponent)
		{
			// All components must be registered with the engine.
			newComponent->RegisterComponent();

			// Hydrate the component from the save data.
			FMemoryReader MemoryReader(componentSaveData.serializedData);
			FObjectAndNameAsStringProxyArchive Archive(MemoryReader, false);
			Archive.ArIsSaveGame = true;
			newComponent->Serialize(Archive);
		}
	}
}
