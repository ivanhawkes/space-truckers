#include "Ships/EngineComponent.h"


UEngineComponent::UEngineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UEngineComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UEngineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

