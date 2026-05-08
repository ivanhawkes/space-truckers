#pragma once

#include "SolarSystem.h"
#include "Sun.generated.h"


USTRUCT(BlueprintType)
struct FSun
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText name;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FSolarSystem solarSystem;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FTransform transform;
};
