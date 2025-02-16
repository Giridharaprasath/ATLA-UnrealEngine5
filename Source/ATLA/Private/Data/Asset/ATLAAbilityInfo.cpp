// Copyright Melon Studios.

#include "Data/Asset/ATLAAbilityInfo.h"
#include "ATLA/ATLA.h"

FAbilityInfo UATLAAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogATLA, Error, TEXT("Can't find Info for AttributeTag [%s] on AbilityInfo [%s]"),
		       *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAbilityInfo();
}
