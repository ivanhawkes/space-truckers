#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "SaveGame/SaveGameSpaceTrucker.h"
#include "SolarSystem.generated.h"

class UGameInstanceSpaceTrucker;


USTRUCT(BlueprintType)
struct FSolarSystem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName id;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText name;
};


UCLASS()
class SPACETRUCKERS_API ASolarSystemActor : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	ASolarSystemActor();

	/** Hook into the tick callback. */
	virtual void Tick(float DeltaTime) override;

	/** Our name for this solar system. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Parameters")
	FString solarSystemName;

	/** Mass is a scale factor vs our own sun. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Parameters")
	double massFactor{0.0f};
	
	/** Density of this sun in comparision to Earth's sun. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Parameters")
	double densityFactor{1.0f};
	
	/** Angular rotation around the axis for this body in degrees. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Orbit")
	double axialRotation{0.0f};
	
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double GetGravity();
	
	/** Returns an indication of whether the axial spin is clockwise or counterclockwise. */
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double IsClockwise() const;
	
	/** Returns 1.0 for anti-clockwise, and -1.0 for clockwise. */
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double SpinDirection() const;
	
	// Called right after spawning each dynamic actor for a new game.
	virtual void OnPostInitialSpawn() override;
	
	// Called right before data serialization.
	virtual bool OnPreSave(FActorSaveData& SaveData) override;
	
	// Called right after data deserialization.
	virtual bool OnPostLoad(FActorSaveData& SaveData) override;
	
	// In-built lifecycle overrides.
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;
	virtual void PostActorCreated() override;
	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UGameInstanceSpaceTrucker* gameInstance;
};
