#include "Ships/TrailerComponent.h"


UTrailerComponent::UTrailerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTrailerComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTrailerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

