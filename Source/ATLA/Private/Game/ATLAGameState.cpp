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

void AATLAGameState::ServerOnCharacterSelected_Implementation(const ECharacterElement CharacterElement)
{
	SelectedCharacterList.Add(CharacterElement, true);

	MulticastOnCharacterSelected(CharacterElement);
	ServerSetSelectedCharactersList(CharacterElement);
}

bool AATLAGameState::CheckIsCharacterSelected(const ECharacterElement CharacterElement)
{
	if (SelectedCharacterList.Contains(CharacterElement))
	{
		return SelectedCharacterList[CharacterElement];
	}
	
	return false;
}

void AATLAGameState::ServerSetSelectedCharactersList_Implementation(const ECharacterElement CharacterElement)
{
}

void AATLAGameState::MulticastOnCharacterSelected_Implementation(const ECharacterElement CharacterElement)
{
	SelectedCharacterList.Add(CharacterElement, true);

	TArray<ECharacterElement> SelectedCharacters;

	for (auto CharacterList : SelectedCharacterList)
	{
		if (CharacterList.Value)
		{
			SelectedCharacters.Add(CharacterList.Key);
		}
	}

	OnCharacterSelected.Broadcast(SelectedCharacters);
}
