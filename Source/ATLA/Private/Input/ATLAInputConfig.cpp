// Copyright Melon Studios.

#include "Input/ATLAInputConfig.h"

#include "ATLA/ATLA.h"

const UInputAction* UATLAInputConfig::FindAbilityInputActionForTag(const FGameplayTag InputTag, bool bLogNotFound) const
{
	for (const FATLAInputAction& InputAction : AbilityInputActions)
	{
		if (InputAction.InputAction && InputAction.InputTag == InputTag)
		{
			return InputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogATLA, Display, TEXT("AIC : Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"),
		       *InputTag.ToString(), *GetNameSafe(this))
	}
	
	return nullptr;
}
