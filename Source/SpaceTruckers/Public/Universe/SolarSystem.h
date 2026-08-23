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
	ASolarSystemActor();

	virtual void Tick(float DeltaTime) override;

	/** Have we already loaded the universe? */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Generation Parameters")
	FString solarSystemName;

	/** Scale the sun according to this factor. */
	UPROPERTY(EditAnywhere, SaveGame, Category = "Generation Parameters")
	FVector sunScale{1.0f, 1.0f, 1.0f};
	
	void SetSunScale();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class USolarSystemComponent* solarSystemComponent;

	// Mesh for our sun.
	UStaticMeshComponent* sunMeshComponent;
};
