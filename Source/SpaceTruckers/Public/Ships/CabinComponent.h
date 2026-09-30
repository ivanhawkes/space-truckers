#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Ships/IVehicleComponent.h"
#include "CabinComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UCabinComponent : public UActorComponent, public IIVehicleComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCabinComponent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/** A mesh that represents this component. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> mesh;

	/** A constraint that connects this component to the main rig. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Physics")
	TObjectPtr<UPhysicsConstraintComponent> physicsConstraint;

protected:
	virtual void BeginPlay() override;
};
