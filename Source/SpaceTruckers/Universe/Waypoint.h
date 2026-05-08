#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Waypoint.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UWaypoint : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWaypoint();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(const float DeltaTime, const ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
