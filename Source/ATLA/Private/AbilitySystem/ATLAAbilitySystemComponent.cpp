// Copyright Melon Studios.

#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ATLAGameplayAbility.h"
#include "ATLA/ATLA.h"

void UATLAAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::ClientEffectApplied);
}

void UATLAAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities,
                                                        int Level)
{
	for (const TSubclassOf AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);

		if (const UATLAGameplayAbility* ATLAAbility = Cast<UATLAGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(ATLAAbility->StartUpInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UATLAAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTag(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UATLAAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTag(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UATLAAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogATLA, Error, TEXT("Failed to execute delegate in %hs"), __FUNCTION__);
		}
	}
}

FGameplayTag UATLAAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->GetAssetTags())
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag("Abilities")))
			{
				return Tag;
			}
		}
	}

	return FGameplayTag();
}

FGameplayTag UATLAAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag Tag : AbilitySpec.GetDynamicSpecSourceTags())
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag("InputTag")))
		{
			return Tag;
		}
	}

	return FGameplayTag();
}

void UATLAAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                     const FGameplayEffectSpec& EffectSpec,
                                                                     FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
