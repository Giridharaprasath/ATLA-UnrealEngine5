// Copyright Melon Studios.

#include "Game/ATLAGameMode.h"

#include "Player/ATLAPlayerController.h"

void AATLAGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AATLAPlayerController* NewATLAPlayerController = Cast<AATLAPlayerController>(NewPlayer);

	ATLAPlayerControllers.Add(NewATLAPlayerController);

	NewATLAPlayerController->OnPlayerJoined();
}

void AATLAGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AATLAPlayerController* ExitingATLAPlayerController = Cast<AATLAPlayerController>(Exiting);

	ATLAPlayerControllers.Remove(ExitingATLAPlayerController);

	ExitingATLAPlayerController->OnPlayerLeft();
}
