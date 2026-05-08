#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "MarketListing.generated.h"


USTRUCT(BlueprintType)
struct FMarketListing : public FTableRowBase
{
	GENERATED_BODY()

	// What item is available for purchase.
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName itemId;

	// De-normalised for performance reasons. This allows us to perform sorts and grouping without a table scan.
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName categoryId;

	// What price is each unit.
	UPROPERTY(EditAnywhere, Category = "Item Data")
	double unitPrice{0.0f};

	// How many units are available.
	UPROPERTY(EditAnywhere, Category = "Item Data")
	int32 unitsAvailable{0};
};
