// Copyright Melon Studios.

#include "AbilitySystem/Data/AttributeInfo.h"

FATLAAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FATLAAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]"),
		       *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FATLAAttributeInfo();
}
