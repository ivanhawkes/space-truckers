#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vehicle.generated.h"


UCLASS()
class SPACETRUCKERS_API AVehicle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
		virtual void Tick(float DeltaTime) override;
};
