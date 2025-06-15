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

bool AATLAPlayerController::GetShowCharacterSelectMenuAtStart_Implementation()
{
	if (bAlwaysShowCharacterSelectMenu) return true;

	// TODO : LATER ADD A SAVE LOAD METHOD TO CHECK TO SHOW CHARACTER SELECT MENU AT START, FOR NOW RETURNING TRUE TO SHOW ALL TIME
	return true;
}

void AATLAPlayerController::ServerOnCharacterSelected_Implementation(const ECharacterElement CharacterElement)
{
	if (AATLAGameMode* ATLAGameMode = Cast<AATLAGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ATLAGameMode->SpawnSelectedCharacter(this, CharacterElement);
	}
}

void AATLAPlayerController::ClientOnCharacterSelected_Implementation(bool bIsSuccessful, ECharacterElement CharacterElement)
{
	if (bIsSuccessful)
	{
		bOnCharacterSelected = true;
	}
	
	OnCharacterSelected.Broadcast(bIsSuccessful, CharacterElement);
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

	ATLAHUD->OnHUDInit.AddDynamic(this, &ThisClass::OnHUDInitialized);
	if (ATLAHUD->bHUDInitialized)
	{
		OnHUDInitialized(true);
	}
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

void AATLAPlayerController::ServerCreateOtherPlayerInfoHUD_Implementation()
{
	if (AATLAGameState* ATLAGameState = Cast<AATLAGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		ATLAGameState->MulticastCreateOtherPlayerInfoHUD();
	}
}

void AATLAPlayerController::OnHUDInitialized(bool bIsSuccessful)
{
	if (!bIsSuccessful)
	{
		UE_LOG(LogATLA, Display, TEXT("PC : On HUD Initialize Returned False"));
		return;
	}

	ATLAHUD->OnHUDInit.RemoveDynamic(this, &ThisClass::OnHUDInitialized);

	if (GetShowCharacterSelectMenuAtStart())
	{
		ATLAHUD->OpenCharacterSelectUIWidget();
	}
}

void AATLAPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetATLAASC() == nullptr) return;

	GetATLAASC()->AbilityInputTagPressed(InputTag);
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
