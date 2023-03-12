// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAAbilitySystemComponent.h"

void UATLAAbilitySystemComponent::ReceiveDamage(UATLAAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}