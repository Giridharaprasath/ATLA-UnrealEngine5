// Copyright Melon Studios.

#include "Character/ATLAPlayer.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/ATLAHUD.h"
#include "Player/ATLAPlayerController.h"
#include "Player/ATLAPlayerState.h"

AATLAPlayer::AATLAPlayer()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AATLAPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// * Init Ability Actor Info for the Sever
	InitAbilityActorInfo();
}

void AATLAPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// * Init Ability Actor Info for the Client
	InitAbilityActorInfo();
}

int32 AATLAPlayer::GetPlayerLevel()
{
	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	check(ATLAPlayerState);
	
	return ATLAPlayerState->GetPlayerLevel();
}

void AATLAPlayer::InitAbilityActorInfo()
{
	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	check(ATLAPlayerState);

	ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, this);
	Cast<UATLAAbilitySystemComponent>(ATLAPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = ATLAPlayerState->GetAbilitySystemComponent();
	AttributeSet = ATLAPlayerState->GetAttributeSet();

	// TODO : FIND ANOTHER METHOD TO INIT PLAYER HUD
	if (AATLAPlayerController* ATLAPlayerController = Cast<AATLAPlayerController>(GetController()))
	{
		if (AATLAHUD* ATLAHUD = Cast<AATLAHUD>(ATLAPlayerController->GetHUD()))
		{
			ATLAHUD->InitPlayerHUD(ATLAPlayerController, ATLAPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}
