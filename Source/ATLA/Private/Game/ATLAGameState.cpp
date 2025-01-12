// Copyright Melon Studios.

#include "Game/ATLAGameState.h"
#include "GameFramework/PlayerState.h"
#include "HUD/ATLAHUD.h"
#include "Player/ATLAPlayerController.h"

void AATLAGameState::MulticastCreateOtherPlayerInfoHUD_Implementation()
{
	for (const APlayerState* PlayerState : PlayerArray)
	{
		if (const AATLAPlayerController* ATLAPlayerController = Cast<AATLAPlayerController>(PlayerState->GetPlayerController()))
		{
			if (const AATLAHUD* ATLAHUD = Cast<AATLAHUD>(ATLAPlayerController->GetHUD()))
			{
				ATLAHUD->CreateOtherPlayerInfoHUD();
			}
		}
	}
}
