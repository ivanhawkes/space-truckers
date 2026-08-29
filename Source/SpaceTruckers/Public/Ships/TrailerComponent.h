#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrailerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACETRUCKERS_API UTrailerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
		UTrailerComponent();

protected:
		virtual void BeginPlay() override;

public:
		virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
