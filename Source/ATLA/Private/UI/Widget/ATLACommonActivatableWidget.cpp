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
