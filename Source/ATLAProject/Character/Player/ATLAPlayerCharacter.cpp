// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAPlayerCharacter.h"
#include "ATLAProject/Character/Abilities/ATLAAbilitySystemComponent.h"

AATLAPlayerCharacter::AATLAPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void AATLAPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	if (ATLAPlayerState)
	{
		InitATLAAbilitySystemComponent(ATLAPlayerState);
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

void AATLAPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	if (ATLAPlayerState)
	{
		InitATLAAbilitySystemComponent(ATLAPlayerState);
		BindASCInput();
	}
}

void AATLAPlayerCharacter::BindASCInput()
{
	if (!ASCInputBound && ATLAAbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		FTopLevelAssetPath AbilityEnumAssetPath = FTopLevelAssetPath(FName("/Script/ATLAProject"), FName("EATLAAbilityID"));
		ATLAAbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,FGameplayAbilityInputBinds(
			FString("ConfirmTarget"), FString("CancelTarget"), AbilityEnumAssetPath,
			static_cast<int32>(EATLAAbilityID::Confirm), static_cast<int32>(EATLAAbilityID::Cancel)));

		ASCInputBound = true;
	}
}

void AATLAPlayerCharacter::InitATLAAbilitySystemComponent(AATLAPlayerState* ATLAPlayerState)
{
	ATLAAbilitySystemComponent = Cast<UATLAAbilitySystemComponent>(ATLAPlayerState->GetAbilitySystemComponent());
	ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, this);
	CharacterAttributeSetBase = ATLAPlayerState->GetAttributeSetBase();
	ATLAAbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	InitializeAttributes();
	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());
	SetStamina(GetMaxStamina());
}

void AATLAPlayerCharacter::ActivateAbilityInputID(bool Activate, const EATLAAbilityID AbilityInputID)
{
	if (ATLAAbilitySystemComponent.IsValid())
	{
		if (Activate)
		{
			ATLAAbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(AbilityInputID));
		}
		else
		{
			ATLAAbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(AbilityInputID));
		}
	}
}