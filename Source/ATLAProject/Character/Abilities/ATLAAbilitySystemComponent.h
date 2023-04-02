// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ATLAAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UATLAAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

/**
 * ATLA Ability System Component Class.
 */
UCLASS()
class ATLAPROJECT_API UATLAAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	// To Broadcasts On ReceivedDamage whenever this ASC receives Damage.
	virtual void ReceiveDamage(UATLAAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
};