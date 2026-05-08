#pragma once

#include "Engine/DataTable.h"
#include "MarketItem.generated.h"


// Standardised measure unit for trading.
UENUM()
enum class EMeasurementType : uint8
{
   // Sold individually.
   Unit UMETA(DisplayName = "Unit"),

   // SI unit for weight.
   Gram UMETA(DisplayName = "Gram"),

   // Sold by weight.
   Kilogram UMETA(DisplayName = "Kilogram"),

   // Metric ton 1000kg.
   Tonne UMETA(DisplayName = "Tonne"),

   // SI unit for length.
   Metre UMETA(DisplayName = "Metre"),

   // SI unit for area.
   SquareMetre UMETA(DisplayName = "Square Metre"),

   // SI unit for volume.
   Litre UMETA(DisplayName = "Litre"),

   // Large volumes.
   CubicMetre UMETA(DisplayName = "Cubic Metre"),

   // Standard unit for electrical power.
   KilowattHours UMETA(DisplayName = "Kilowatt-Hours")
};


USTRUCT(BlueprintType)
struct FMarketItem : public FTableRowBase
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FText name;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FText description;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FName categoryId;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   int32 stackSize{1};

   // The price for this item given balanced values for all variables like supply, demand, travel distances, economy.
   // This allows us to set reasonable centre points for pricing.
   UPROPERTY(EditAnywhere, Category = "Item Data")
   double basePrice{0.0f};

   // Standardised measurement unit for this item type.
   UPROPERTY(EditAnywhere, Category = "Item Data")
   EMeasurementType measurementType{EMeasurementType::Unit};
};
