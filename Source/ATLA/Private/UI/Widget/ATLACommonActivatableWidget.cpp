// Copyright Melon Studios.

#include "UI/Widget/ATLACommonActivatableWidget.h"
#include "ATLA/ATLA.h"

void UATLACommonActivatableWidget::ReturnFocusBackToGame_Implementation()
{
	if (APlayerController* Controller = GetOwningPlayer(); Controller != nullptr)
	{
		Controller->bShowMouseCursor = false;
		const FInputModeGameOnly InputModeData;
		Controller->SetInputMode(InputModeData);

		UE_LOG(LogATLA, Display, TEXT("Returning Focus Back to Game"));
	}
}

void UATLACommonActivatableWidget::SetMouseCursorState_Implementation(bool bShowMouseCursor)
{
	if (APlayerController* Controller = GetOwningPlayer(); Controller != nullptr)
	{
		Controller->bShowMouseCursor = bShowMouseCursor;

		UE_LOG(LogATLA, Display, TEXT("Set Show Mouse Cursor State : %hhd"), bShowMouseCursor);
	}
}

void UATLACommonActivatableWidget::StartDeactivateWidget_Implementation()
{
	DeactivateWidget();
}
