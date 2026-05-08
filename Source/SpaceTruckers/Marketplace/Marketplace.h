#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Marketplace.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACETRUCKERS_API UMarketplace : public UActorComponent
{
   GENERATED_BODY()

public:
   // Sets default values for this component's properties
   UMarketplace();

protected:
   // Called when the game starts
   virtual void BeginPlay() override;

public:
   // Called every frame
   virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                              FActorComponentTickFunction* ThisTickFunction) override;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FName id;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FText name;

   UPROPERTY(EditAnywhere, Category = "Item Data")
   FText description;

   // All calculations are scaled by this factor for purchases.
   // This provides an easy, across the board way to over / under pay the value of the items traded.
   UPROPERTY(EditAnywhere, Category = "Item Data")
   double purchaseFactor{1.0f};

   // All calculations are scaled by this factor for sales.
   // This provides an easy, across the board way to over / under selll the value of the items traded.
   UPROPERTY(EditAnywhere, Category = "Item Data")
   double saleFactor{1.2f};
};
