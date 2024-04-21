// Copyright Melon Studios.

#include "Character/ATLAPlayer.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

void AATLAPlayer::InitAbilityActorInfo()
{
	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	check(ATLAPlayerState);

	ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, this);
	AbilitySystemComponent = ATLAPlayerState->GetAbilitySystemComponent();
	AttributeSet = ATLAPlayerState->GetAttributeSet();
}
