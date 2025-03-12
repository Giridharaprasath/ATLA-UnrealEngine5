// Copyright Melon Studios.

#include "AbilitySystem/Abilities/Common/ATLAGameplayAbility_Vision.h"

UATLAGameplayAbility_Vision::UATLAGameplayAbility_Vision(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}
