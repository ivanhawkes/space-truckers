#pragma once

#include "MarketItemCategory.generated.h"


// Defines the type of the item.
UENUM()
enum class EMarketCategoryType : uint8
{
	Alloy UMETA(DisplayName = "Alloys"),
	Appliances UMETA(DisplayName = "Appliances"),
	Arms UMETA(DisplayName = "Arms"),
	Chemicals UMETA(DisplayName = "Chemicals"),
	Communication UMETA(DisplayName = "Communications"),
	Computing UMETA(DisplayName = "Computing"),
	ConstructionMaterial UMETA(DisplayName = "Construction Material"),
	Consumable UMETA(DisplayName = "Consumable"),
	Drugs UMETA(DisplayName = "Drugs"),
	Entertainment UMETA(DisplayName = "Entertainment"),
	Fertiliser UMETA(DisplayName = "Fertiliser"),
	Fuel UMETA(DisplayName = "Fuel"),
	Luxury UMETA(DisplayName = "Luxury Goods"),
	Machinery UMETA(DisplayName = "Machinery"),
	MedicalEquipment UMETA(DisplayName = "Medical Equipment"),
	Metal UMETA(DisplayName = "Metal"),
	Minerals UMETA(DisplayName = "Minerals"),
	MiningEquipment UMETA(DisplayName = "Mining Equipment"),
	Optics UMETA(DisplayName = "Optics"),
	Pharmaceutical UMETA(DisplayName = "Pharmaceutical"),
	Polymer UMETA(DisplayName = "Polymer"),
	Seeds UMETA(DisplayName = "Seeds"),
	Slaves UMETA(DisplayName = "Slaves"),
	SmallArms UMETA(DisplayName = "Small Arms"),
	Textiles UMETA(DisplayName = "Textiles"),
	Tool UMETA(DisplayName = "Tool"),
	Water UMETA(DisplayName = "Water")
};


USTRUCT(BlueprintType)
struct FMarketItemCategory : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText name;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText description;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EMarketCategoryType categoryType{EMarketCategoryType::Water};
};
