#pragma once

#include "Sun.h"
#include "Planet.generated.h"


USTRUCT(BlueprintType)
struct FPlanet
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FText name;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FSun solarSystem;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FTransform transform;
};
