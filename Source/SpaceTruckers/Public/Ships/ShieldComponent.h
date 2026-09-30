#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ships/IVehicleComponent.h"
#include "ShieldComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UShieldComponent : public UActorComponent, public IIVehicleComponent
{
	GENERATED_BODY()

public:
		UShieldComponent();

protected:
		virtual void BeginPlay() override;

public:
		virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
