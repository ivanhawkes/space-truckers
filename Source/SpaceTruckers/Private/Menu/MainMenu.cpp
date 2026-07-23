// 
#include "SpaceTruckers/Public/Menu/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void UMainMenu::OnStartGame()
{
	// Hide menu
	RemoveFromParent();
    
	// Start game
	UGameplayStatics::OpenLevel(GetWorld(), "Test 01");
}

void UMainMenu::OnQuitGame() const
{
	// Quit game
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("Exit");
}
