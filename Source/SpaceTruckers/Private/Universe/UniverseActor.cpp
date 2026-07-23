#include "SpaceTruckers/Public/Universe/UniverseActor.h"
#include "SpaceTruckers/Public/Universe/UniverseComponent.h"


// Sets default values
AUniverseActor::AUniverseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	universeComponent = CreateDefaultSubobject<UUniverseComponent>(TEXT("Universe"), false);
}


// Called when the game starts or when spawned
void AUniverseActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AUniverseActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
