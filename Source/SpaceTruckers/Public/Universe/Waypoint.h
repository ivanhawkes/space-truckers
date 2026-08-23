#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Waypoint.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UWaypoint : public UActorComponent
{
	GENERATED_BODY()

public:
		UWaypoint();

		virtual void BeginPlay() override;

		virtual void TickComponent(const float DeltaTime, const ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
