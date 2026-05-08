#pragma once

#include "Planet.h"
#include "Satellite.generated.h"


USTRUCT(BlueprintType)
struct FSatellite
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText name;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FPlanet planet;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FTransform transform;
};
