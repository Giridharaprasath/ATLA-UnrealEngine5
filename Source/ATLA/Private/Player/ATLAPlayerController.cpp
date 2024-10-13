// Copyright Melon Studios.

#include "Player/ATLAPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "ATLA/ATLA.h"
#include "Game/ATLAGameMode.h"
#include "HUD/ATLAHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ATLAPlayerState.h"

AATLAPlayerController::AATLAPlayerController()
{
	bReplicates = true;
}

void AATLAPlayerController::ClientOnPlayerLeft_Implementation()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	OnPlayerJoined();
}

void AATLAPlayerController::ClientOnPlayerJoined_Implementation()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	OnPlayerLeft();
}

void AATLAPlayerController::OnPlayerJoined_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("PC : On New Player Joined"));
}

void AATLAPlayerController::OnPlayerLeft_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("PC : On A Player Left"));
}

void AATLAPlayerController::OpenPauseMenu_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("PC : On Open Pause Menu"));

	GetATLAHUD()->OpenPauseMenu();
}

void AATLAPlayerController::ClientSpawnSelectedPlayer_Implementation(const FName CharacterName)
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	UE_LOG(LogATLA, Display, TEXT("PC : On Client Spawn Selected Player Character Name: %s"), *CharacterName.ToString());

	ServerSpawnSelectedPlayer(CharacterName);
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

void AATLAPlayerController::ServerSpawnSelectedPlayer_Implementation(const FName CharacterName)
{
	UE_LOG(LogATLA, Display, TEXT("PC : On Server Spawn Selected Player Character Name: %s"), *CharacterName.ToString());

	if (AATLAGameMode* ATLAGameMode = Cast<AATLAGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ATLAGameMode->SpawnSelectedCharacter(this, CharacterName);
	}
}
