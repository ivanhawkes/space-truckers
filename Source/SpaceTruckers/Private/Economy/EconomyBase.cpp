#include "Economy/EconomyBase.h"


UEconomyBase::UEconomyBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UEconomyBase::BeginPlay()
{
	Super::BeginPlay();
}


void UEconomyBase::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
