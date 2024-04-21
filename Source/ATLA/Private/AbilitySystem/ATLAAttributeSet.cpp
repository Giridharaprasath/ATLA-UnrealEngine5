// Copyright Melon Studios.

#include "AbilitySystem/ATLAAttributeSet.h"
#include "Net/UnrealNetwork.h"

UATLAAttributeSet::UATLAAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitStamina(100.f);
	InitMaxStamina(100.f);
}

void UATLAAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UATLAAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UATLAAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UATLAAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UATLAAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UATLAAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATLAAttributeSet, Health, OldHealth);
}

void UATLAAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATLAAttributeSet, MaxHealth, OldMaxHealth);
}

void UATLAAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATLAAttributeSet, Stamina, OldStamina);
}

void UATLAAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATLAAttributeSet, MaxStamina, OldMaxStamina);	
}
