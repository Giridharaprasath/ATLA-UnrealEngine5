// Copyright Melon Studios.

#include "UI/Widget/PlayerHUD/ATLAPlayerHUD.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ATLAPlayerState.h"
#include "UI/WidgetController/PlayerHUDWidgetController.h"

void UATLAPlayerHUD::CreateOtherPlayerInfoWidget()
{
	OtherPlayerInfoVerticalBox->ClearChildren();

	for (auto PlayerState : UGameplayStatics::GetGameState(GetWorld())->PlayerArray)
	{
		APlayerController* PC = PlayerState->GetPlayerController();
		if (GetOwningPlayer() == PC) continue;
		
		AATLAPlayerState* PS = Cast<AATLAPlayerState>(PlayerState);
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		UAttributeSet* AS = PS->GetAttributeSet();
		
		const FWidgetController OtherPlayerInfoWC(PC, PS, ASC, AS);
		TObjectPtr<UPlayerHUDWidgetController> OtherPlayerWC = NewObject<UPlayerHUDWidgetController>(this, PlayerHUDWidgetControllerClass);
		OtherPlayerWC->SetWidgetController(OtherPlayerInfoWC);
		OtherPlayerWC->BindCallbacksToDependencies();

		UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OtherPlayerInfoWidgetClass);
		TObjectPtr<UATLAUserWidget> OtherPlayerHUDWidget = Cast<UATLAUserWidget>(UserWidget);

		OtherPlayerHUDWidget->SetWidgetController(OtherPlayerWC);
		OtherPlayerWC->BroadcastInitialValues();

		OtherPlayerInfoVerticalBox->AddChildToVerticalBox(OtherPlayerHUDWidget);
	}
}
