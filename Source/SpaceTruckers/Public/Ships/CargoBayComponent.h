#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ships/IVehicleComponent.h"
#include "CargoBayComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UCargoBayComponent : public UActorComponent, public IIVehicleComponent
{
	GENERATED_BODY()

public:
		UCargoBayComponent();

protected:
		virtual void BeginPlay() override;

public:
		virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
