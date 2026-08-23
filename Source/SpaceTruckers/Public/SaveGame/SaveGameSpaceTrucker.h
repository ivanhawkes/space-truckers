#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Templates/SubclassOf.h"
#include "SaveGameSpaceTrucker.generated.h"

class AActor;


USTRUCT(BlueprintType)
struct FActorSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FString name;

	UPROPERTY()
	TSubclassOf<AActor> actorClass;

	UPROPERTY()
	FTransform transform;

	UPROPERTY()
	TArray<uint8> serializedData;
};


UCLASS()
class SPACETRUCKERS_API USaveGameSpaceTrucker : public USaveGame
{
	GENERATED_BODY()

public:
	// Dynamically spawned actors. Will need to be despawned and respawned for loading and saving.
	UPROPERTY()
	TArray<FActorSaveData> SavedDynamicActors;
	
	// Example of player state tracking
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FVector playerLocation;
	
	// Track the last map the player used.
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FString lastMapName;
};
