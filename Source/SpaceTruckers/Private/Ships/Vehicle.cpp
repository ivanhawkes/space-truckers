#include "Ships/Vehicle.h"


ATruck::AVehicle()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ATruck::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATruck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

