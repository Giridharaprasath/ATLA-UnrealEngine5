// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLACharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "ATLAProject/Character/Abilities/ATLAAbilitySystemComponent.h"
#include "ATLAProject/Character/Abilities/ATLAGameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AATLACharacterBase::AATLACharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	
	bAlwaysRelevant = true;
	
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("Slate.RemoveOnDeath"));
}

// Called when the game starts or when spawned
void AATLACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AATLACharacterBase::GetAbilitySystemComponent() const
{
	return ATLAAbilitySystemComponent.Get();
}

bool AATLACharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 AATLACharacterBase::GetAbilityLevel(EATLAAbilityID AbilityID) const
{
	return 1;
}

void AATLACharacterBase::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !ATLAAbilitySystemComponent.IsValid() || !ATLAAbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : ATLAAbilitySystemComponent->GetActivatableAbilities())
	{
		if (Spec.SourceObject == this && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		ATLAAbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	ATLAAbilitySystemComponent->bCharacterAbilitiesGiven = false;
}

void AATLACharacterBase::Die()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (ATLAAbilitySystemComponent.IsValid())
	{
		ATLAAbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = ATLAAbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);

		ATLAAbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void AATLACharacterBase::FinishDying()
{
	Destroy();
}

int32 AATLACharacterBase::GetCharacterLevel() const
{
	if (CharacterAttributeSetBase.IsValid())
	{
		return CharacterAttributeSetBase->GetCharacterLevel();
	}
	
	return 0;
}


float AATLACharacterBase::GetHealth() const
{
	if (CharacterAttributeSetBase.IsValid())
	{
		return CharacterAttributeSetBase->GetHealth();
	}
	return 0.0f;
}

float AATLACharacterBase::GetMaxHealth() const
{
	if (CharacterAttributeSetBase.IsValid())
	{
		return CharacterAttributeSetBase->GetMaxHealth();
	}
	return 0.0f;
}

float AATLACharacterBase::GetMana() const
{
	if (CharacterAttributeSetBase.IsValid())
	{
		return CharacterAttributeSetBase->GetMana();
	}
	return 0.0f;
}

float AATLACharacterBase::GetMaxMana() const
{
	if (CharacterAttributeSetBase.IsValid())
	{
		return CharacterAttributeSetBase->GetMaxMana();
	}
	return 0.0f;
}

float AATLACharacterBase::GetStamina() const
{
	if (CharacterAttributeSetBase.IsValid())
	{
		return CharacterAttributeSetBase->GetStamina();
	}
	return 0.0f;
}

float AATLACharacterBase::GetMaxStamina() const
{
	if (CharacterAttributeSetBase.IsValid())
	{
		return CharacterAttributeSetBase->GetMaxStamina();
	}
	return 0.0f;
}

void AATLACharacterBase::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !ATLAAbilitySystemComponent.IsValid() || ATLAAbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UATLAGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		ATLAAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility,
			GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	ATLAAbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

void AATLACharacterBase::InitializeAttributes()
{
	if (!ATLAAbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = ATLAAbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = ATLAAbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = ATLAAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), ATLAAbilitySystemComponent.Get());
	}
}

void AATLACharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority && !ATLAAbilitySystemComponent.IsValid() && ATLAAbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = ATLAAbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = ATLAAbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = ATLAAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), ATLAAbilitySystemComponent.Get());
		}
	}

	ATLAAbilitySystemComponent->bStartupEffectsApplied = true;
}

void AATLACharacterBase::SetHealth(float Health)
{
	if (CharacterAttributeSetBase.IsValid())
	{
		CharacterAttributeSetBase->SetHealth(Health);
	}
}

void AATLACharacterBase::SetMana(float Mana)
{
	if (CharacterAttributeSetBase.IsValid())
	{
		CharacterAttributeSetBase->SetMana(Mana);
	}
}

void AATLACharacterBase::SetStamina(float Stamina)
{
	if (CharacterAttributeSetBase.IsValid())
	{
		CharacterAttributeSetBase->SetStamina(Stamina);
	}
}