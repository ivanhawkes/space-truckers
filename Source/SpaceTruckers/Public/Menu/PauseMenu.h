// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class SPACETRUCKERS_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnResumeGame();

	UFUNCTION(BlueprintCallable)
	void OnMainMenu();
};
