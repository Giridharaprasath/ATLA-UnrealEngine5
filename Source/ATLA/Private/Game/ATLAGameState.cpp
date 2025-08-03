// Copyright Melon Studios.

#include "Game/ATLAGameState.h"
#include "MVVMGameSubsystem.h"
#include "Enum/ECharacterElement.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/ATLAPlayerController.h"
#include "ViewModel/CharacterSelectMenuViewModel.h"

AATLAGameState::AATLAGameState()
{
	for (const ECharacterElement CharacterElement : TEnumRange<ECharacterElement>())
	{
		SelectedCharacterInfo.Add(*new FSelectedCharacter(false, CharacterElement));
	}
}

void AATLAGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AATLAGameState, SelectedCharacterInfo);
}

void AATLAGameState::MulticastCreateOtherPlayerInfoHUD_Implementation()
{
	for (const APlayerState* PlayerState : PlayerArray)
	{
		if (AATLAPlayerController* ATLAPlayerController = Cast<AATLAPlayerController>(PlayerState->GetPlayerController()))
		{
			ATLAPlayerController->ClientCreateOtherPlayerInfoHUD();
		}
	}
}

bool AATLAGameState::CheckIsCharacterSelected(const ECharacterElement CharacterElement) const
{
	for (int i = 0; i < SelectedCharacterInfo.Num(); i++)
	{
		if (SelectedCharacterInfo[i].CharacterElement == CharacterElement)
		{
			return SelectedCharacterInfo[i].bIsSelected;
		}
	}
	return false;
}

void AATLAGameState::ServerOnCharacterSelected_Implementation(const ECharacterElement CharacterElement)
{
	for (int i = 0; i < SelectedCharacterInfo.Num(); i++)
	{
		if (SelectedCharacterInfo[i].CharacterElement == CharacterElement)
		{
			SelectedCharacterInfo[i].bIsSelected = true;
		}
	}
	SetSelectedCharacterInViewModel();
}

void AATLAGameState::ServerOnCharacterDeselected_Implementation(const ECharacterElement CharacterElement)
{
	for (int i = 0; i < SelectedCharacterInfo.Num(); i++)
	{
		if (SelectedCharacterInfo[i].CharacterElement == CharacterElement)
		{
			SelectedCharacterInfo[i].bIsSelected = false;
		}
	}
	SetSelectedCharacterInViewModel();
}

void AATLAGameState::BeginPlay()
{
	CreateCharacterSelectMenuViewModel();
	Super::BeginPlay();
}

void AATLAGameState::OnRep_SelectedCharacterInfo()
{
	SetSelectedCharacterInViewModel();
}

void AATLAGameState::CreateCharacterSelectMenuViewModel()
{
	CharacterSelectMenuViewModel = NewObject<UCharacterSelectMenuViewModel>(this, CharacterSelectMenuViewModelClass);
}

void AATLAGameState::SetSelectedCharacterInViewModel()
{
	for (const FSelectedCharacter SelectedCharacter : SelectedCharacterInfo)
	{
		switch (SelectedCharacter.CharacterElement)
		{
		case ECharacterElement::Air:
			CharacterSelectMenuViewModel->SetIsAirSelected(SelectedCharacter.bIsSelected);
			break;
		case ECharacterElement::Water:
			CharacterSelectMenuViewModel->SetIsWaterSelected(SelectedCharacter.bIsSelected);
			break;
		case ECharacterElement::Earth:
			CharacterSelectMenuViewModel->SetIsEarthSelected(SelectedCharacter.bIsSelected);
			break;
		case ECharacterElement::Fire:
			CharacterSelectMenuViewModel->SetIsFireSelected(SelectedCharacter.bIsSelected);
			break;
		case ECharacterElement::NonBender:
			break;
		default:
			break;
		}
	}
}
