// Developed By Melon Studios.

#include "ATLAAbilityHUDCommonUI.h"
#include "Input/CommonUIInputTypes.h"

void UATLAAbilityHUDCommonUI::ShowResetBinding()
{
	if (!GetActionBindings().Contains(ResetHandle))
	{
		AddActionBinding(ResetHandle);
	}
}

void UATLAAbilityHUDCommonUI::HideResetBinding()
{
	RemoveActionBinding(ResetHandle);
}

void UATLAAbilityHUDCommonUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResetHandle = RegisterUIActionBinding(FBindUIActionArgs(ResetInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleResetAction)));
}