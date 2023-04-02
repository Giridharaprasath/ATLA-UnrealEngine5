// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAPlayerController.h"
#include "ATLAPlayerState.h"
#include "ATLAProject/HUD/ATLAHUD.h"
#include "AbilitySystemComponent.h"
//#include "ATLAProject/Character/Player/ATLAPlayerCharacter.h"

void AATLAPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();

	if (ATLAPlayerState)
	{
		ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, InPawn);
	}
}

void AATLAPlayerController::CreatePlayerHUD(const FText& CharacterName)
{
	if (!IsLocalPlayerController())
	{
		return;
	}
	
	AATLAHUD* ATLAHUD = GetHUD<AATLAHUD>();
	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	//AATLAPlayerCharacter* ATLAPlayerCharacter = GetPawn<AATLAPlayerCharacter>();
	
	if (ATLAHUD)
	{
		ATLAHUD->CreatePlayerHUD();

		if (ATLAPlayerState)
		{
			ATLAHUD->SetPlayerHealthBar(ATLAPlayerState->GetHealth() / FMath::Max(ATLAPlayerState->GetMaxHealth(), 1.f));
		}
		
		/*if (ATLAPlayerCharacter)
		{
			ATLAHUD->SetCharacterName(ATLAPlayerCharacter->GetCharacterName());
		}*/

		ATLAHUD->SetCharacterName(CharacterName);
	}
}