// Developed By Melon Studios.

#include "ATLAPlayerCharacter.h"
#include "ATLAProject/Character/Abilities/ATLAAbilitySystemComponent.h"
#include "ATLAProject/Character/Abilities/ATLAGameplayAbility.h"
#include "EnhancedInputComponent.h"

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

void AATLAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		if (IA_Ability_1)
		{
			EnhancedInputComponent->BindAction(IA_Ability_1, ETriggerEvent::Triggered, this, &ThisClass::HandleInputPressed_Ability_1);
			EnhancedInputComponent->BindAction(IA_Ability_1, ETriggerEvent::Completed, this, &ThisClass::HandleInputReleased_Ability_1);
		}

		if (IA_Ability_2)
		{
			EnhancedInputComponent->BindAction(IA_Ability_2, ETriggerEvent::Triggered, this, &ThisClass::HandleInputPressed_Ability_2);
			EnhancedInputComponent->BindAction(IA_Ability_2, ETriggerEvent::Completed, this, &ThisClass::HandleInputReleased_Ability_2);
		}

		if (IA_Ability_3)
		{
			EnhancedInputComponent->BindAction(IA_Ability_3, ETriggerEvent::Triggered, this, &ThisClass::HandleInputPressed_Ability_3);
			EnhancedInputComponent->BindAction(IA_Ability_3, ETriggerEvent::Completed, this, &ThisClass::HandleInputReleased_Ability_3);
		}

		if (IA_Ability_4)
		{
			EnhancedInputComponent->BindAction(IA_Ability_4, ETriggerEvent::Triggered, this, &ThisClass::HandleInputPressed_Ability_4);
			EnhancedInputComponent->BindAction(IA_Ability_4, ETriggerEvent::Completed, this, &ThisClass::HandleInputReleased_Ability_4);
		}
	}
}

void AATLAPlayerCharacter::GiveNewAbility(TSubclassOf<UATLAGameplayAbility> AbilityClass)
{
	if (!HasAuthority() || !ATLAAbilitySystemComponent.IsValid())
	{
		return;
	}

	ATLAAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass,
	GetAbilityLevel(AbilityClass.GetDefaultObject()->AbilityID), static_cast<int32>(AbilityClass.GetDefaultObject()->AbilityInputID), this));
}

void AATLAPlayerCharacter::GetAllAvailableAbilities()
{
	TArray<FGameplayAbilitySpec> AvailableAbilities = ATLAAbilitySystemComponent->GetActivatableAbilities();
	for (const FGameplayAbilitySpec& Ability : AvailableAbilities)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
			FString::Printf(TEXT("Ability Level: %d"), Ability.InputID));
	}
}

void AATLAPlayerCharacter::HandleInputPressed_Ability_1()
{
	if (Ability_1)
	{
		ActivateAbilityInputID(true, Ability_1.GetDefaultObject()->AbilityID);
	}
}

void AATLAPlayerCharacter::HandleInputReleased_Ability_1()
{
	if (Ability_1)
	{
		ActivateAbilityInputID(false, Ability_1.GetDefaultObject()->AbilityID);
	}
}

void AATLAPlayerCharacter::HandleInputPressed_Ability_2()
{
	if (Ability_2)
	{
		ActivateAbilityInputID(true, Ability_2.GetDefaultObject()->AbilityID);
	}
}

void AATLAPlayerCharacter::HandleInputReleased_Ability_2()
{
	if (Ability_2)
	{
		ActivateAbilityInputID(false, Ability_2.GetDefaultObject()->AbilityID);
	}
}

void AATLAPlayerCharacter::HandleInputPressed_Ability_3()
{
	if (Ability_3)
	{
		ActivateAbilityInputID(true, Ability_3.GetDefaultObject()->AbilityID);
	}
}

void AATLAPlayerCharacter::HandleInputReleased_Ability_3()
{
	if (Ability_3)
	{
		ActivateAbilityInputID(false, Ability_3.GetDefaultObject()->AbilityID);
	}
}

void AATLAPlayerCharacter::HandleInputPressed_Ability_4()
{
	if (Ability_4)
	{
		ActivateAbilityInputID(true, Ability_4.GetDefaultObject()->AbilityID);
	}
}

void AATLAPlayerCharacter::HandleInputReleased_Ability_4()
{
	if (Ability_4)
	{
		ActivateAbilityInputID(false, Ability_4.GetDefaultObject()->AbilityID);
	}
}