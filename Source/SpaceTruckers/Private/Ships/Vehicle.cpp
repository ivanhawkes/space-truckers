#include "Ships/Vehicle.h"


AVehicle::AVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and set the base mesh as the root component.
	sceneRoot = CreateDefaultSubobject<USceneComponent >(TEXT("SceneRoot"));
	SetRootComponent(sceneRoot);

	// Create some components that every vehicle needs.
	cabinComponent = CreateDefaultSubobject<UCabinComponent>(TEXT("CabinComponent"));
}


void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}


void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

