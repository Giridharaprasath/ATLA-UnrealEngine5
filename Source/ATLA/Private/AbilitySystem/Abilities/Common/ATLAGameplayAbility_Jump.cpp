// Copyright Melon Studios.

#include "AbilitySystem/Abilities/Common/ATLAGameplayAbility_Jump.h"

#include "Character/ATLACharacterBase.h"

UATLAGameplayAbility_Jump::UATLAGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UATLAGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}

	const AATLACharacterBase* ATLACharacter = Cast<AATLACharacterBase>(ActorInfo->AvatarActor.Get());
	if (!ATLACharacter || !ATLACharacter->CanJump())
	{
		return false;
	}
	
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UATLAGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	CharacterJumpStop();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UATLAGameplayAbility_Jump::CharacterJumpStart()
{
	if (AATLACharacterBase* ATLACharacter = GetATLACharacterFromActorInfo())
	{
		if (ATLACharacter->IsLocallyControlled() && !ATLACharacter->bPressedJump)
		{
			ATLACharacter->UnCrouch();
			ATLACharacter->Jump();
		}
	}
}

void UATLAGameplayAbility_Jump::CharacterJumpStop()
{
	if (AATLACharacterBase* ATLACharacter = GetATLACharacterFromActorInfo())
	{
		if (ATLACharacter->IsLocallyControlled() && ATLACharacter->bPressedJump)
		{
			ATLACharacter->StopJumping();
		}
	}
}


