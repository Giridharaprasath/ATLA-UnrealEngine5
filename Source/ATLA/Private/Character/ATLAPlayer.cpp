// Copyright Melon Studios.

#include "Character/ATLAPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

AATLAPlayer::AATLAPlayer()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}