#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Truck.generated.h"


UCLASS()
class SPACETRUCKERS_API ATruck : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATruck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
		virtual void Tick(float DeltaTime) override;
};
