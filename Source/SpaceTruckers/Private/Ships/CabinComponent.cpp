#include "Ships/CabinComponent.h"


UCabinComponent::UCabinComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCabinComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCabinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

