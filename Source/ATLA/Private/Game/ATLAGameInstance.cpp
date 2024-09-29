// Copyright Melon Studios.

#include "Game/ATLAGameInstance.h"
#include "ATLA/ATLA.h"
#include "Kismet/GameplayStatics.h"

void UATLAGameInstance::ExitToDesktop_Implementation()
{
}

void UATLAGameInstance::ExitToMainMenu_Implementation()
{
}

void UATLAGameInstance::GoToMainMenuLevel_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("Go To Main Menu Level"));

	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MainMenuLevel, true, "?listen");
}
