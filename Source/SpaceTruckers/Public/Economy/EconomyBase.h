#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EconomyBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UEconomyBase : public UActorComponent
{
	GENERATED_BODY()

public:
		UEconomyBase();
	
		virtual void BeginPlay() override;

		virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
