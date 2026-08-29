#pragma once

#include "Planet.h"
#include "SaveGame/SaveGameSpaceTrucker.h"
#include "Satellite.generated.h"

class APlanetActor;
class UGameInstanceSpaceTrucker;


UCLASS()
class SPACETRUCKERS_API ASatelliteActor : public AActor, public ISavableActorInterface
{
	GENERATED_BODY()

public:
	ASatelliteActor();

	/** Hook into the tick callback. */
	virtual void Tick(float DeltaTime) override;

	/** Our name for the satellite. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Parameters")
	FString satelliteName;

	/** The mass is a scale factor vs the International Space Station. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Parameters")
	double massFactor{0.0f};
	
	/** Density of this satellite in comparision to the International Space Station. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Parameters")
	double densityFactor{1.0f};
	
	/** A reference to the actor around which this body is in orbit. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Parameters")
	TObjectPtr<APlanetActor> orbitParent;

	/** The base distance from the orbit centre. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Orbit")
	double orbitRadius;

	/** Present orbit rotation around the central mass in degrees. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Orbit")
	double orbitRotation{0.0f};
	
	/** Angular rotation around the axis for this body in degrees. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Orbit")
	double axialRotation{0.0f};
	
	/** Calculates the gravity of a body using its mass and the gravitational constant. */
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double GetGravity() const;
	
	/** Calculates the orbit radius from the body it is orbiting. */
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double GetOrbitDistance() const;
	
	/** Calculates the orbit velocity of a body using its gravity and distance from the body it is orbiting. */
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double GetOrbitCircularVelocity() const;
	
	/** Converts the velocity to the time period it takes to orbit the central mass in seconds. */
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double GetOrbitPeriod() const;
	
	/** Converts the velocity to an angular value in radians per second. */
	UFUNCTION(BlueprintCallable, Category = "Orbit")
	double GetVelocityInRadiansPerSecond() const;
	
	// Called right after spawning each dynamic actor for a new game.
	virtual void OnPostInitialSpawn() override;
	
	// Called right before data serialization.
	virtual bool OnPreSave(FActorSaveData& SaveData) override;
	
	// Called right after data deserialization.
	virtual bool OnPostLoad(FActorSaveData& SaveData) override;

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UGameInstanceSpaceTrucker* gameInstance;
};
