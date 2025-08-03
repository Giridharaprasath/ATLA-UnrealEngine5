// Copyright Melon Studios.

#include "ViewModel/CharacterSelectMenuViewModel.h"

bool UCharacterSelectMenuViewModel::GetIsAirSelected() const
{
	return bIsAirSelected;
}

bool UCharacterSelectMenuViewModel::GetIsWaterSelected() const
{
	return bIsWaterSelected;
}

bool UCharacterSelectMenuViewModel::GetIsEarthSelected() const
{
	return bIsEarthSelected;
}

bool UCharacterSelectMenuViewModel::GetIsFireSelected() const
{
	return bIsFireSelected;
}

void UCharacterSelectMenuViewModel::SetIsAirSelected(const bool bNewIsAirSelected)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsAirSelected, bNewIsAirSelected))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(bIsAirSelected);
	}
}

void UCharacterSelectMenuViewModel::SetIsWaterSelected(const bool bNewIsWaterSelected)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsWaterSelected, bNewIsWaterSelected))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(bIsWaterSelected);
	}
}

void UCharacterSelectMenuViewModel::SetIsEarthSelected(const bool bNewIsEarthSelected)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsEarthSelected, bNewIsEarthSelected))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(bIsEarthSelected);
	}
}

void UCharacterSelectMenuViewModel::SetIsFireSelected(const bool bNewIsFireSelected)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsFireSelected, bNewIsFireSelected))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(bIsFireSelected);
	}
}
