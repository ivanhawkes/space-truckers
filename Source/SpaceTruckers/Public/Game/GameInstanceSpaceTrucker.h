#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "GameInstanceSpaceTrucker.generated.h"


class ASolarSystemActor;
class APlanetActor;
class ASatelliteActor;
class USaveGameSpaceTrucker;
struct FActorSaveData;


USTRUCT(BlueprintType)
struct FOrbitParameters
{
	GENERATED_BODY()

public:
	/** The minimum distance to the point of rotation for this orbit. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite)
	double deadZone{1000.0f};

	/** The algorithm will step this many degrees of rotation for each iteration of generation. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite)
	double fixedRotationDegree{47.0f};

	/** The algorithm will add or subtract this amount of random rotation. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite)
	double randomRotationDegree{18.0f};

	/** The algorithm will step this many metres outwards for each iteration of generation. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite)
	double fixedExpansionOutward{300.0f};

	/** The algorithm will add or subtract this amount of random outward distance. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite)
	double randomExpansionOutward{32.0f};
};


USTRUCT(BlueprintType)
struct FUniverseParameters
{
	GENERATED_BODY()

public:
	/** A name for our beloved home. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	FText name;

	/** Universes with the same seed value will be identical in their randomness. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	int64 randomSeed{0};

	/** A table that contains the list of names we will select from to name the solar systems. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	UDataTable* solarSystemNames;

	/** A table that contains the list of names we will select from to name the planets. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	UDataTable* planetNames;

	/** The number of solar systems to generate. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	int32 numberOfSolarSystems{50};

	/** The minimum number of planets to generate. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	int32 minNumberOfPlanets{2};

	/** The maximum number of planets to generate. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	int32 maxNumberOfPlanets{12};

	/** The minimum number of satellites to generate. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	int32 minNumberOfSatellites{2};

	/** The maximum number of satellites to generate. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Universe Parameters")
	int32 maxNumberOfSatellites{12};
};


UCLASS()
class SPACETRUCKERS_API UGameInstanceSpaceTrucker : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UGameInstanceSpaceTrucker();
	virtual void Init() override;
	virtual void Shutdown() override;

	// FTickableGameObject
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	void LoadUniverse();

	/** Have we already generated the solar system and planets? */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Generation Parameters")
	bool shouldGenerate{false};

	/** Have we already loaded the universe? */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Generation Parameters")
	bool shouldLoadUniverse{false};

	/** All the parameters needed to create our universe. */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	FUniverseParameters universeParameters;

	/** Empty space at the centre of the galaxy. There is a black hole at the centre of every galaxy. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Solar System Orbit Parameters")
	FOrbitParameters solarSystemOrbit;
	
	/** Empty space at the centre of the galaxy. There is a black hole at the centre of every galaxy. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Planetary Orbit Parameters")
	FOrbitParameters planetOrbit;

	/** Empty space at the centre of the galaxy. There is a black hole at the centre of every galaxy. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Satellite Orbit Parameters")
	FOrbitParameters satelliteOrbit;
	
	/** The number of seconds of gameplay since the level was spawned. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Gameplay")
	float gameplaySeconds{0.0f};
	
	/** A factor used to multiply the realtime clock to produce time in game seconds. */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Gameplay")
	float timeMultiplier{2400.0f};
	
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

	// Blueprint subclass for solar systems.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<ASolarSystemActor> bpSolarSystem;

	// Blueprint subclass for planets.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<APlanetActor> bpPlanet;

	// Blueprint subclass for satellites.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<ASatelliteActor> bpSatellite;

protected:
	// Callback function when any world fires its BeginPlay
	void OnWorldInitialized(UWorld* NewWorld, const UWorld::InitializationValues IVS);

private:
	/** Create everything needed for a fresh universe. */
	void GenerateNewUniverse(UWorld* NewWorld);

	/** Dynamically create actors for each solar system. */
	void CreateSolarSystems(UWorld* NewWorld, FRandomStream RandomStream, const TArray<FName>& SolarSystemNameList,
	                        const TArray<FName>& PlanetNameList);

	/** Dynamically create actors for each planet. */
	void CreatePlanets(UWorld* NewWorld, FRandomStream RandomStream, const TObjectPtr<ASolarSystemActor> OrbitParent,
	                   const TArray<FName>& PlanetNameList);

	/** Dynamically create actors for each satellite. */
	void CreateSatellites(UWorld* NewWorld, FRandomStream RandomStream, const TObjectPtr<APlanetActor> OrbitParent,
					   const TArray<FName>& PlanetNameList);

	// Remove all the dynamic actors we spawned.
	void ClearCurrentDynamicActors();

	// Save the generated content.
	void SaveDynamicActors(USaveGameSpaceTrucker* saveGame);
	void SaveActorComponents(AActor* TargetActor, FActorSaveData& SaveData);

	// Load the generated content.
	void LoadDynamicActors(USaveGameSpaceTrucker* saveGame);
	void LoadActorComponents(AActor* TargetActor, FActorSaveData& SaveData);

	// Used to track which name was last used in the list.
	int32 planetNameIndex{0};
	int32 satelliteNameIndex{0};
	
	// Used short term to recall the slot name used for loading a level. Because level load is
	// deferred we need to store the parameters for later.
	FString slotName;
};
