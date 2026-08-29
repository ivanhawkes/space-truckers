#include "Ships/ShieldComponent.h"


UShieldComponent::UShieldComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

