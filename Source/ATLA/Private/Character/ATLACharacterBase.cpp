// Copyright Melon Studios.

#include "Character/ATLACharacterBase.h"
#include "AbilitySystemComponent.h"
#include "ATLAGameplayTags.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "Component/Character/ATLACharacterMovementComponent.h"

AATLACharacterBase::AATLACharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UATLACharacterMovementComponent>(CharacterMovementComponentName))
{
	UATLACharacterMovementComponent* ATLAMoveComp = CastChecked<UATLACharacterMovementComponent>(GetCharacterMovement());
	ATLAMoveComp->GravityScale = 2.0f;
	ATLAMoveComp->MaxAcceleration = 1500.0f;
	ATLAMoveComp->BrakingFrictionFactor = 1.0f;
	ATLAMoveComp->BrakingFriction = 6.0f;
	ATLAMoveComp->GroundFriction = 8.0f;
	ATLAMoveComp->MaxWalkSpeed = 500.0f;
	ATLAMoveComp->MaxWalkSpeedCrouched = 200.0f;
	ATLAMoveComp->MinAnalogWalkSpeed = 20.0f;
	ATLAMoveComp->BrakingDecelerationWalking = 1400.0f;
	ATLAMoveComp->bCanWalkOffLedges = true;
	ATLAMoveComp->bCanWalkOffLedgesWhenCrouching = true;
	ATLAMoveComp->JumpZVelocity = 720.0f;
	ATLAMoveComp->AirControl = 0.35f;
	ATLAMoveComp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	ATLAMoveComp->bUseControllerDesiredRotation = true;
	ATLAMoveComp->bOrientRotationToMovement = true;
	ATLAMoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	ATLAMoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	ATLAMoveComp->SetCrouchedHalfHeight(65.0f);

	PrimaryActorTick.bCanEverTick = false;
}

UATLAAbilitySystemComponent* AATLACharacterBase::GetATLAAbilitySystemComponent() const
{
	return Cast<UATLAAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* AATLACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

ECharacterElement AATLACharacterBase::GetCharacterElement() const
{
	return CharacterElement;
}

ECharacterType AATLACharacterBase::GetCharacterType() const
{
	return CharacterType;
}

void AATLACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AATLACharacterBase::InitAbilityActorInfo()
{
}

void AATLACharacterBase::InitializeDefaultAttributes() const
{
}

void AATLACharacterBase::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	const UATLACharacterMovementComponent* ATLAMoveComp = CastChecked<UATLACharacterMovementComponent>(GetCharacterMovement());

	SetMovementModeTag(PrevMovementMode, PreviousCustomMode, false);
	SetMovementModeTag(ATLAMoveComp->MovementMode, ATLAMoveComp->CustomMovementMode, true);
}

void AATLACharacterBase::SetMovementModeTag(const EMovementMode MovementMode, uint8 CustomMovementMode, const bool bTagEnabled) const
{
	if (UATLAAbilitySystemComponent* ATLAASC = GetATLAAbilitySystemComponent())
	{
		const FGameplayTag* MovementModeTag = nullptr;
		if (MovementMode == MOVE_Walking)
			MovementModeTag = &FATLAGameplayTags::Get().MovementMode_Walking;
		else if (MovementMode == MOVE_Falling)
			MovementModeTag = &FATLAGameplayTags::Get().MovementMode_Falling;

		if (MovementModeTag && MovementModeTag->IsValid())
		{
			ATLAASC->SetLooseGameplayTagCount(*MovementModeTag, bTagEnabled ? 1 : 0);
		}
	}
}
