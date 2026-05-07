#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UniverseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACETRUCKERS_API UUniverseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUniverseComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void GenerateNewUniverse();

	/** Universes with the same seed value will be identical in their randomness.  */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	uint32 randomSeed;

	/** A table that contains the list of names we will select from for solar systems. */
	UPROPERTY(EditAnywhere)
	UDataTable* solarSystemNames;

	/** A table that contains the list of names we will select from for planets. */
	UPROPERTY(EditAnywhere)
	UDataTable* PlanetNames;

	/** Empty space at the centre of the galaxy. There is a black hole at the centre of every galaxy. */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	float deadZone {1000.0f};

	/** The algorithm will step this many degrees of rotation for each iteration of solar system generation. */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	float fixedRotationDegree {60.0f};

	/** The algorithm will add or subtract this amount of random rotation. */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	float randomRotationDegree {0.0f};

	/** The algorithm will step this many metres outwards for each iteration of solar system generation. */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	float fixedExpansionOutward {100.0f};

	/** The algorithm will add or subtract this amount of random outward distance. */
	UPROPERTY(EditAnywhere, Category = "Generation Parameters")
	float randomExpansionOutward {0.0f};
};
