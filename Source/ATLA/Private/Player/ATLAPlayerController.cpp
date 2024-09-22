// Copyright Melon Studios.

#include "Player/ATLAPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "ATLA/ATLA.h"
#include "HUD/ATLAHUD.h"
#include "Player/ATLAPlayerState.h"

AATLAPlayerController::AATLAPlayerController()
{
	bReplicates = true;
}

void AATLAPlayerController::OnPlayerJoined_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("New Player Joined"));
}

void AATLAPlayerController::OnPlayerLeft_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("A Player Left"));
}

void AATLAPlayerController::OpenPauseMenu_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("Open Pause Menu"));

	GetATLAHUD()->OpenPauseMenu();
}

void AATLAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalPlayerController())
	{
		return;
	}

	ATLAHUD = GetHUD<AATLAHUD>();
	ATLAPlayerState = GetPlayerState<AATLAPlayerState>();

	check(UIGenericControls);
	check(ATLAPlayerControls);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(UIGenericControls, 0);
	Subsystem->AddMappingContext(ATLAPlayerControls, 0);

	// TODO : REMOVE THIS WHEN ADDING CHARACTER SELECTION AT FIRST
	bShowMouseCursor = false;

	const FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
}
