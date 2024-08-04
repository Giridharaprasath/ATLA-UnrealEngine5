// Copyright Melon Studios.

#include "AbilitySystem/ATLAAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/ATLAHUD.h"
#include "Player/ATLAPlayerState.h"
#include "UI/WidgetController/ATLAWidgetController.h"

UPlayerHUDWidgetController* UATLAAbilitySystemLibrary::GetPlayerHUDWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AATLAHUD* ATLAHUD = Cast<AATLAHUD>(PC->GetHUD()))
		{
			AATLAPlayerState* PS = PC->GetPlayerState<AATLAPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetController WidgetController(PC, PS, ASC, AS);
			
			return ATLAHUD->GetPlayerHUDWidgetController(WidgetController);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UATLAAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AATLAHUD* ATLAHUD = Cast<AATLAHUD>(PC->GetHUD()))
		{
			AATLAPlayerState* PS = PC->GetPlayerState<AATLAPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetController WidgetController(PC, PS, ASC, AS);
			
			return ATLAHUD->GetAttributeMenuWidgetController(WidgetController);
		}
	}

	return nullptr;
}
