#include "Ships/ComputerComponent.h"


UComputerComponent::UComputerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UComputerComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UComputerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

