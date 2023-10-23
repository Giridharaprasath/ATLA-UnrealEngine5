// Developed By Melon Studios.

#include "ATLAAbilitySystemComponent.h"

void UATLAAbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 NewLevel)
{
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);

	if (AbilitySpec)
	{
		AbilitySpec->Level = NewLevel;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UATLAAbilitySystemComponent::ReceiveDamage(UATLAAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}