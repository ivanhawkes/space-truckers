#pragma once

#include "MarketItemCategory.generated.h"


// Defines the type of the item.
UENUM()
enum class EMarketCategoryType : uint8
{
	Alcohol UMETA(DisplayName = "Alcohol"),
	Alloys UMETA(DisplayName = "Alloys"),
	Animals UMETA(DisplayName = "Animals"),
	AnimalProducts UMETA(DisplayName = "AnimalProducts"),
	Appliances UMETA(DisplayName = "Appliances"),
	Arms UMETA(DisplayName = "Arms"),
	Chemicals UMETA(DisplayName = "Chemicals"),
	Collectibles UMETA(DisplayName = "Collectibles"),
	Communications UMETA(DisplayName = "Communications"),
	Computing UMETA(DisplayName = "Computing"),
	ConstructionMaterials UMETA(DisplayName = "Construction Materials"),
	Consumables UMETA(DisplayName = "Consumables"),
	Crafts UMETA(DisplayName = "Crafts"),
	Currency UMETA(DisplayName = "Currency"),
	Drugs UMETA(DisplayName = "Drugs"),
	Electronics UMETA(DisplayName = "Electronics"),
	Engineering UMETA(DisplayName = "Engineering"),
	Entertainment UMETA(DisplayName = "Entertainment"),
	FarmingEquipment UMETA(DisplayName = "FarmingEquipment"),
	Ferments UMETA(DisplayName = "Ferments"),
	Fertilisers UMETA(DisplayName = "Fertilisers"),
	Fuels UMETA(DisplayName = "Fuels"),
	Humans UMETA(DisplayName = "Humans"),
	Information UMETA(DisplayName = "Information"),
	LuxuryGoods UMETA(DisplayName = "Luxury Goods"),
	Machinery UMETA(DisplayName = "Machinery"),
	MedicalEquipment UMETA(DisplayName = "Medical Equipment"),
	Medicine UMETA(DisplayName = "Medicine"),
	Metals UMETA(DisplayName = "Metals"),
	Minerals UMETA(DisplayName = "Minerals"),
	MiningEquipment UMETA(DisplayName = "Mining Equipment"),
	Optics UMETA(DisplayName = "Optics"),
	Pharmaceuticals UMETA(DisplayName = "Pharmaceuticals"),
	Polymers UMETA(DisplayName = "Polymers"),
	ScientificEquipment UMETA(DisplayName = "ScientificEquipment"),
	Seeds UMETA(DisplayName = "Seeds"),
	Slaves UMETA(DisplayName = "Slaves"),
	SmallArms UMETA(DisplayName = "Small Arms"),
	Textiles UMETA(DisplayName = "Textiles"),
	Tools UMETA(DisplayName = "Tools"),
	Water UMETA(DisplayName = "Water"),
	Writing UMETA(DisplayName = "Writing")
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
