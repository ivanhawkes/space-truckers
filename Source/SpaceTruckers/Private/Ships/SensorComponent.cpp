#include "Ships/SensorComponent.h"


USensorComponent::USensorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USensorComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USensorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

