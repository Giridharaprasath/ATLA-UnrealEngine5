// Developed By Melon Studios.

#include "ATLAGameState.h"
#include "ATLAProject/HUD/ATLAHUD.h"
#include "ATLAProject/Player/ATLAPlayerController.h"
#include "GameFramework/PlayerState.h"

void AATLAGameState::SetDiscordPartySize_Implementation()
{
	const int PartySize = PlayerArray.Num();
	for (APlayerState* PlayerState : PlayerArray)
	{
		AATLAPlayerController* ATLAPlayerController = Cast<AATLAPlayerController>(PlayerState->GetPlayerController());

		if (ATLAPlayerController)
		{
			ATLAPlayerController->SetDiscordPartySize(PartySize);
		}
	}
}

void AATLAGameState::MulticastCreateTeamHUD_Implementation()
{
	for (APlayerState* PlayerState : PlayerArray)
	{
		AATLAPlayerController* ATLAPlayerController = Cast<AATLAPlayerController>(PlayerState->GetPlayerController());

		if (ATLAPlayerController)
		{
			AATLAHUD* ATLAHUD = ATLAPlayerController->GetATLAHUD();

			if (ATLAHUD)
			{
				ATLAHUD->CreateTeamHUD();
			}
		}
	}
}