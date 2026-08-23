#include "SpaceTruckers/Public/Marketplace/Marketplace.h"


UMarketplace::UMarketplace()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMarketplace::BeginPlay()
{
	Super::BeginPlay();
}


void UMarketplace::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
