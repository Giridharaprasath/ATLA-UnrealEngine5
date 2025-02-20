// Copyright Melon Studios.

#include "AbilitySystem/Abilities/ATLAGameplayAbility.h"
#include "Character/ATLACharacterBase.h"

AATLACharacterBase* UATLAGameplayAbility::GetATLACharacterFromActorInfo() const
{
	return CurrentActorInfo ? Cast<AATLACharacterBase>(CurrentActorInfo->AvatarActor.Get()) : nullptr;
}
