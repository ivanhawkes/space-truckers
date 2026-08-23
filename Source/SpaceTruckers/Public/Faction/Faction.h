#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Faction.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UFaction : public UActorComponent
{
	GENERATED_BODY()

public:
		UFaction();

		virtual void BeginPlay() override;

		virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
