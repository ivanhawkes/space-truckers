#pragma once

#include "CoreMinimal.h"
#include "CabinComponent.h"
#include "GameFramework/Pawn.h"
#include "Ships/IVehicleComponent.h"
#include "Vehicle.generated.h"


UCLASS()
class SPACETRUCKERS_API AVehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVehicle();

	/** A mesh that represents this component. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Mesh")
	TObjectPtr<USceneComponent> sceneRoot;

	/** A constraint that connects this component to the main rig. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Physics")
	TObjectPtr<UPhysicsConstraintComponent> physicsConstraint;

	/** A constraint that connects this component to the main rig. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Physics")
	TObjectPtr<UCabinComponent> cabinComponent;
	
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
