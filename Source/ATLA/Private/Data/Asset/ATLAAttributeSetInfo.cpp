// Copyright Melon Studios.

#include "Data/Asset/ATLAAttributeSetInfo.h"
#include "ATLA/ATLA.h"

FAttributeSetInfo UATLAAttributeSetInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAttributeSetInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogATLA, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]"),
		       *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAttributeSetInfo();
}
