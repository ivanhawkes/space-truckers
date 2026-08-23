#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameInstanceSpaceTrucker.generated.h"

class USaveGameSpaceTrucker;


USTRUCT(BlueprintType)
struct FUniverseParameters
{
	GENERATED_BODY()

public:
	/** A name for our beloved home. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	FText name;
	
	/** Universes with the same seed value will be identical in their randomness. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	int64 randomSeed{0};

	/** A table that contains the list of names we will select from to name the solar systems. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	UDataTable* solarSystemNames;

	/** A table that contains the list of names we will select from to name the planets. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	UDataTable* planetNames;

	/** Empty space at the centre of the galaxy. There is a black hole at the centre of every galaxy. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	float deadZone{1000.0f};
	
	/** The algorithm will step this many degrees of rotation for each iteration of solar system generation. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	float fixedRotationDegree{47.0f};

	/** The algorithm will add or subtract this amount of random rotation. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	float randomRotationDegree{18.0f};

	/** The algorithm will step this many metres outwards for each iteration of solar system generation. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	float fixedExpansionOutward{300.0f};

	/** The algorithm will add or subtract this amount of random outward distance. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Generation Parameters")
	float randomExpansionOutward{32.0f};
};


UCLASS()
class SPACETRUCKERS_API UGameInstanceSpaceTrucker : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	/** Have we already generated the solar system and planets? */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Generation Parameters")
	bool shouldGenerate{false};
	
	/** Have we already loaded the universe? */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Generation Parameters")
	bool shouldLoadUniverse{false};
	
	/** All the parameters needed to create our universe. */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	FUniverseParameters universeParameters;
	
	// A shadow list containing all of the generated solar systems.
	 UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "References")
	TArray<TObjectPtr<AActor>> solarSystemShadowList;
	
	UFUNCTION(BlueprintCallable, Category = "Level Management")
	void SaveLevelAndPlayerState(FString SlotName);

	UFUNCTION(BlueprintCallable, Category = "Level Management")
	void LoadLevelAndPlayerState(FString SlotName);

	UFUNCTION(BlueprintCallable, Category = "LevelManagement", meta=(WorldContext="WorldContextObject"))
	void NewLevelFromTemplate(
		const UObject* WorldContextObject,
		const TSoftObjectPtr<UWorld> Level,
		int64 randomSeed,
		UDataTable* SolarSystemNames,
		UDataTable* PlanetNames
	);

protected:
	// Callback function when any world fires its BeginPlay
	void OnWorldInitialized(UWorld* newWorld, const UWorld::InitializationValues IVS);

private:
	/** Create all the actors needed to populate a fresh universe. */
	void GenerateNewUniverse(UWorld* newWorld);

	// Remove all the dynamic actors we spawned.
	void ClearCurrentDynamicActors();

	// Save the generated content.
	void SaveDynamicActors(USaveGameSpaceTrucker* saveGame);
	void SaveActor(USaveGameSpaceTrucker* saveGame, TObjectPtr<AActor> actor);
	
	// Load the generated content.
	void LoadDynamicActors();
};
