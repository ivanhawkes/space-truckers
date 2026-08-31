#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ships/IVehicleComponent.h"
#include "EngineComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UEngineComponent : public UActorComponent, public IIVehicleComponent
{
	GENERATED_BODY()

public:
		UEngineComponent();

protected:
		virtual void BeginPlay() override;

public:
		virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
