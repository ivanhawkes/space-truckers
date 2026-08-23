#include "SpaceTruckers/Public/Universe/Waypoint.h"


UWaypoint::UWaypoint()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWaypoint::BeginPlay()
{
	Super::BeginPlay();
}


void UWaypoint::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
