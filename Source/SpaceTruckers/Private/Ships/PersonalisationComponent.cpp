#include "Ships/PersonalisationComponent.h"


UPersonalisationComponent::UPersonalisationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPersonalisationComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UPersonalisationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

