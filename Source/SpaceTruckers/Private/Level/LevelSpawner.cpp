#include "Level/LevelSpawner.h"
#include "Engine/World.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "ObjectTools.h"

// Define the signature for the completion delegate
typedef FDelegateHandle OnSpawnCompleteDelegate;

void Spawn(const UWorld* World,
           FName TemplateLevelName,
           TSubclassOf<AActor> EntityClassToSpawn,
           int32 NumberOfEntities
)
{
	// Check if the world still exists and is valid before attempting to spawn
	if (!World || !EntityClassToSpawn || EntityClassToSpawn->IsChildOf(AActor::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn failed: World or Entity class is invalid."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Level is ready. Starting to spawn %d entities..."), NumberOfEntities);

	// -----------------------------------------------------------------------
	// STEP 3: Spawn Entities
	// -----------------------------------------------------------------------

	for (int32 i = 0; i < NumberOfEntities; ++i)
	{
		// Generate a random location within the world bounds (simplified for example)
		FVector SpawnLocation = FVector(
			FMath::RandRange(-5000.0f, 5000.0f),
			FMath::RandRange(-5000.0f, 5000.0f),
			FMath::RandRange(0.0f, 1000.0f)
		);

		// Define the rotation (e.g., no rotation)
		FRotator SpawnRotation = FRotator::ZeroRotator;

		// Spawn the actor using UGameplayStatics
		// AActor* NewActor = World->SpawnActor(
		// 	World,
		// 	EntityClassToSpawn,
		// 	SpawnLocation,
		// 	SpawnRotation
		// );

		// if (NewActor)
		// {
		// 	// Success
		// 	UE_LOG(LogTemp, Display, TEXT("Spawned Entity %d at %s"), i + 1, *SpawnLocation.ToString());
		// }
		// else
		// {
		// 	// Failure
		// 	UE_LOG(LogTemp, Error, TEXT("Failed to spawn entity %d."), i + 1);
		// }
	}

	// -----------------------------------------------------------------------
	// STEP 4: Call Callback
	// -----------------------------------------------------------------------
	// OnSpawnComplete.Broadcast();
}



void CreateLevelFromTemplate2(FName LevelName)
{
	// 1. Load the empty level template from your Content directory
	UWorld* TemplateWorld = Cast<UWorld>(StaticLoadObject(UWorld::StaticClass(), NULL, LevelName.ToString()));
    
	if (!TemplateWorld) return;

	// 2. Set up the package and group name for the new level
	// ObjectTools::FPackageGroupName PGN;
	// PGN.ObjectName = TEXT("MyNewEmptyLevel");
	// PGN.PackageName = TEXT("/Game/Levels/MyNewEmptyLevel");
	//
	// TSet<UPackage*> ObjectsUserRefusedToFullyLoad;

	// 3. Duplicate the template world
	// UWorld* NewWorld = CastChecked<UWorld>(ObjectTools::DuplicateSingleObject(TemplateWorld, PGN, ObjectsUserRefusedToFullyLoad));
 //    
	// // 4. (Optional) Prompt the editor to save the newly created package
	// if (NewWorld)
	// {
	// 	UPackage* WorldPackage = NewWorld->GetPackage();
	// 	WorldPackage->MarkPackageDirty();
	// 	// FEditorFileUtils::PromptForCheckoutAndSave({ WorldPackage }, true, false);
	// }
}


void ULevelSpawner::NewLevelFromTemplate(
	const UObject* WorldContextObject,
	const TSoftObjectPtr<UWorld> Level,
	TSubclassOf<AActor> EntityClassToSpawn,
	int32 NumberOfEntities)
{
	// Get the current World context
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadAndSpawnEntities failed: No valid UWorld found."));
		return;
	}

	const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(Level.ToString()));

	// Load the level and start playback.
	// UGameplayStatics::OpenLevel(WorldContextObject, LevelName, true);
	
	// Create a new level.
	CreateLevelFromTemplate2(LevelName);
}
