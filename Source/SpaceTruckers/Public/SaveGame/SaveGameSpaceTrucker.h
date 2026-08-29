#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Templates/SubclassOf.h"
#include "SaveGameSpaceTrucker.generated.h"

class AActor;


USTRUCT(BlueprintType)
struct FComponentSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FName name;

	UPROPERTY()
	TSubclassOf<UActorComponent> componentClass;
	
	UPROPERTY()
	TArray<uint8> serializedData;
};


USTRUCT(BlueprintType)
struct FActorSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FName name;

	UPROPERTY()
	TSubclassOf<AActor> actorClass;

	UPROPERTY()
	FVector location;

	UPROPERTY()
	FRotator rotation;

	UPROPERTY()
	TArray<uint8> serializedData;

	UPROPERTY()
	TArray<FComponentSaveData> dynamicComponents;
};


UCLASS()
class SPACETRUCKERS_API USaveGameSpaceTrucker : public USaveGame
{
	GENERATED_BODY()

public:
	// Dynamically spawned actors. Will need to be despawned and respawned for loading and saving.
	UPROPERTY()
	TArray<FActorSaveData> savedDynamicActors;

	/** The number of seconds of gameplay since the level was spawned. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "SaveData")
	float gameplaySeconds{0.0f};
	
	/** A factor used to multiply the realtime clock to produce time in game seconds. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "SaveData")
	float timeMultiplier{24.0f};
	
	// Example of player state tracking
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FVector playerLocation;

	// Track the last map the player used.
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FString lastMapName;
};


UINTERFACE(MinimalAPI, Blueprintable)
class USavableActorInterface : public UInterface
{
	GENERATED_BODY()
};

class SPACETRUCKERS_API ISavableActorInterface
{
	GENERATED_BODY()

public:
	// Called right after spawning each dynamic actor for a new game.
	virtual void OnPostInitialSpawn() = 0;

	// Called right before data serialization.
	virtual bool OnPreSave(FActorSaveData& SaveData) = 0;

	// Called right after data deserialization.
	virtual bool OnPostLoad(FActorSaveData& SaveData) = 0;
};


UINTERFACE(MinimalAPI, Blueprintable)
class USavableComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class SPACETRUCKERS_API ISavableComponentInterface
{
	GENERATED_BODY()

public:
	// Called right before data serialization.
	virtual void OnPreSave(FComponentSaveData& SaveData) = 0;

	// Called right after data deserialization.
	virtual void OnPostLoad(FComponentSaveData& SaveData) = 0;
};
