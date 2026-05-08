#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarSystem.generated.h"


USTRUCT(BlueprintType)
struct FSolarSystem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName id;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText name;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FTransform transform;
};


UCLASS()
class SPACETRUCKERS_API ASolarSystemActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASolarSystemActor();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class USolarSystemComponent* solarSystemComponent;
	
	UStaticMeshComponent* meshComponent;
};
