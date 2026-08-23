#include "SpaceTruckers/Public/Universe/UniverseActor.h"
#include "Engine/Engine.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"


AUniverseActor::AUniverseActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AUniverseActor::BeginPlay()
{
	Super::BeginPlay();
}


void AUniverseActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
