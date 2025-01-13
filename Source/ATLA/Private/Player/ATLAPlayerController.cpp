// Copyright Melon Studios.

#include "Player/ATLAPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "ATLA/ATLA.h"
#include "Game/ATLAGameMode.h"
#include "Game/ATLAGameState.h"
#include "HUD/ATLAHUD.h"
#include "Input/ATLAInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ATLAPlayerState.h"

AATLAPlayerController::AATLAPlayerController()
{
	bReplicates = true;
}

void AATLAPlayerController::ClientOnPlayerJoined_Implementation()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	OnPlayerJoined();
}

void AATLAPlayerController::ClientOnPlayerLeft_Implementation()
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

void AATLAPlayerController::ClientSpawnSelectedPlayer_Implementation(const FName CharacterName)
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	UE_LOG(LogATLA, Display, TEXT("PC : On Client Spawn Selected Player Character Name : %s"),
	       *CharacterName.ToString());

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

	const FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
}

void AATLAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UATLAInputComponent* ATLAInputComponent = CastChecked<UATLAInputComponent>(InputComponent);
	ATLAInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed,
	                                       &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AATLAPlayerController::OpenPauseMenu_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("PC : On Open Pause Menu"));

	GetATLAHUD()->OpenPauseMenu();
}

void AATLAPlayerController::OpenAttributesMenu_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("PC : On Open Attributes Menu"));

	GetATLAHUD()->OpenAttributesMenu();
}

void AATLAPlayerController::ServerSpawnSelectedPlayer_Implementation(const FName CharacterName)
{
	UE_LOG(LogATLA, Display, TEXT("PC : On Server Spawn Selected Player Character Name : %s"),
	       *CharacterName.ToString());

	if (AATLAGameMode* ATLAGameMode = Cast<AATLAGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ATLAGameMode->SpawnSelectedCharacter(this, CharacterName);
	}
}

void AATLAPlayerController::ServerCreateOtherPlayerInfoHUD_Implementation()
{
	if (AATLAGameState* ATLAGameState = Cast<AATLAGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		ATLAGameState->MulticastCreateOtherPlayerInfoHUD();
	}	
}

void AATLAPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void AATLAPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetATLAASC() == nullptr) return;

	GetATLAASC()->AbilityInputTagReleased(InputTag);
}

void AATLAPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetATLAASC() == nullptr) return;

	GetATLAASC()->AbilityInputTagHeld(InputTag);
}

UATLAAbilitySystemComponent* AATLAPlayerController::GetATLAASC()
{
	if (ATLAAbilitySystemComponent == nullptr)
	{
		ATLAAbilitySystemComponent = Cast<UATLAAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return ATLAAbilitySystemComponent;
}
