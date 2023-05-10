// Developed By Melon Studios.

#include "ATLAGameMode.h"

void AATLAGameMode::OnPostLogin(AController* NewPlayer)
{
	AATLAPlayerController* NewATLAPlayerController = Cast<AATLAPlayerController>(NewPlayer);

	ATLAPlayerControllers.Add(NewATLAPlayerController);

	NewATLAPlayerController->ServerCreateTeamHUD_Implementation();
}

void AATLAGameMode::Logout(AController* Exiting)
{
	AATLAPlayerController* LeavingATLAPlayerController = Cast<AATLAPlayerController>(Exiting);

	ATLAPlayerControllers.Remove(LeavingATLAPlayerController);

	LeavingATLAPlayerController->ServerCreateTeamHUD_Implementation();
}