// Copyright Melon Studios.

#include "Player/ATLAPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "ATLA/ATLA.h"

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

void AATLAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalPlayerController())
	{
		return;
	}

	check(ATLAPlayerControls);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(ATLAPlayerControls, 0);

	// TODO : REMOVE THIS WHEN ADDING CHARACTER SELECTION AT FIRST
	bShowMouseCursor = false;

	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
}
