// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAPlayerState.h"

#include "ATLAPlayerController.h"
#include "ATLAProject/Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "ATLAProject/Character/Abilities/ATLAAbilitySystemComponent.h"
#include "ATLAProject/HUD/ATLAHUD.h"
#include "Net/UnrealNetwork.h"

void AATLAPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (ATLAAbilitySystemComponent)
	{
		HealthChangeDelegateHandle = ATLAAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CharacterAttributeSetBase->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
		MaxHealthChangeDelegateHandle = ATLAAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CharacterAttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::OnMaxHealthChanged);
		
		ManaChangeDelegateHandle = ATLAAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CharacterAttributeSetBase->GetManaAttribute()).AddUObject(this, &ThisClass::OnManaChanged);
		MaxManaChangeDelegateHandle = ATLAAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CharacterAttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &ThisClass::OnMaxManaChanged);
		
		StaminaChangeDelegateHandle = ATLAAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CharacterAttributeSetBase->GetStaminaAttribute()).AddUObject(this, &ThisClass::OnStaminaChanged);
		MaxStaminaChangeDelegateHandle = ATLAAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CharacterAttributeSetBase->GetMaxStaminaAttribute()).AddUObject(this, &ThisClass::OnMaxStaminaChanged);

		CharacterLevelChangeDelegateHandle = ATLAAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			CharacterAttributeSetBase->GetCharacterLevelAttribute()).AddUObject(this, &ThisClass::OnCharacterlevelChanged);

		ATLAAbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")),
			EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnStunTagChanged);
	}
}

AATLAPlayerState::AATLAPlayerState()
{
	ATLAAbilitySystemComponent = CreateDefaultSubobject<UATLAAbilitySystemComponent>(TEXT("ATLAAbilitySystemComponent"));
	ATLAAbilitySystemComponent->SetIsReplicated(true);

	ATLAAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CharacterAttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("CharacterAttributeSetBase"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

FText AATLAPlayerState::GetCharacterName() const 
{
	return CharacterName;
}

void AATLAPlayerState::SetCharacterName(FText NewCharacterName)
{
	CharacterName = NewCharacterName;
}

void AATLAPlayerState::OnRep_CharacterName(const FText OldCharacterName)
{
	if (CharacterName.IsEmpty())
	{
		OnCharacterSelected.Broadcast(false);
	}

	else
	{
		OnCharacterSelected.Broadcast(true);
	}
}

void AATLAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(AATLAPlayerState, CharacterName, COND_None, REPNOTIFY_Always);
}

UAbilitySystemComponent* AATLAPlayerState::GetAbilitySystemComponent() const
{
	return ATLAAbilitySystemComponent;
}

UCharacterAttributeSetBase* AATLAPlayerState::GetAttributeSetBase() const
{
	return CharacterAttributeSetBase;
}

bool AATLAPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void AATLAPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
}

float AATLAPlayerState::GetHealth() const
{
	return CharacterAttributeSetBase->GetHealth();
}

float AATLAPlayerState::GetMaxHealth() const
{
	return CharacterAttributeSetBase->GetMaxHealth();
}

float AATLAPlayerState::GetMana() const
{
	return CharacterAttributeSetBase->GetMana();
}

float AATLAPlayerState::GetMaxMana() const
{
	return CharacterAttributeSetBase->GetMaxMana();
}

float AATLAPlayerState::GetStamina() const
{
	return CharacterAttributeSetBase->GetStamina();
}

float AATLAPlayerState::GetMaxStamina() const
{
	return CharacterAttributeSetBase->GetMaxStamina();
}

int32 AATLAPlayerState::GetCharacterLevel() const
{
	return CharacterAttributeSetBase->GetCharacterLevel();
}

void AATLAPlayerState::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update Player HUD
	AATLAPlayerController* ATLAPlayerController = Cast<AATLAPlayerController>(GetOwner());
	if (ATLAPlayerController)
	{
		AATLAHUD* ATLAHUD = ATLAPlayerController->GetHUD<AATLAHUD>();
		if (ATLAHUD)
		{
			ATLAHUD->SetPlayerHealthBar(Health / GetMaxHealth());
		}
	}

	/*if (!IsAlive() && !ATLAAbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		AATLAPlayerCharacter* ATLAPlayerCharacter = Cast<AATLAPlayerCharacter>(GetPawn());
		if (ATLAPlayerCharacter)
		{
			ATLAPlayerCharacter->Die();
		}
	}*/
	OnHealth.Broadcast(Health / GetMaxHealth());
}

void AATLAPlayerState::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void AATLAPlayerState::OnManaChanged(const FOnAttributeChangeData& Data)
{
}

void AATLAPlayerState::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
}

void AATLAPlayerState::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void AATLAPlayerState::OnMaxStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void AATLAPlayerState::OnCharacterlevelChanged(const FOnAttributeChangeData& Data)
{
}

void AATLAPlayerState::OnStunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		ATLAAbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}