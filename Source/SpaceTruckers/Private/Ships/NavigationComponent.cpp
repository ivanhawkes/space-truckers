#include "Ships/NavigationComponent.h"


UNavigationComponent::UNavigationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UNavigationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UNavigationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

