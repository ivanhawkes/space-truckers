#include "Faction/Faction.h"


UFaction::UFaction()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UFaction::BeginPlay()
{
	Super::BeginPlay();
}


void UFaction::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
