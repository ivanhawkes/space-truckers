#include "Ships/CargoBayComponent.h"


UCargoBayComponent::UCargoBayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCargoBayComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCargoBayComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

