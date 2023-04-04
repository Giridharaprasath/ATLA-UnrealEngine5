// Developed By Melon Studios.

#include "ATLAAbilitySystemComponent.h"

void UATLAAbilitySystemComponent::ReceiveDamage(UATLAAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}