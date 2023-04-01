// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAPlayerController.h"
#include "ATLAPlayerState.h"
#include "ATLAProject/HUD/ATLAHUD.h"
#include "AbilitySystemComponent.h"

void AATLAPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();

	if (ATLAPlayerState)
	{
		ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, InPawn);
	}

	AATLAHUD* ATLAHUD = GetHUD<AATLAHUD>();

	if (ATLAHUD)
	{
		ATLAHUD->CreatePlayerHUD();

		if (ATLAPlayerState)
		{
			ATLAHUD->SetPlayerHealthBar(ATLAPlayerState->GetHealth() / FMath::Max(ATLAPlayerState->GetMaxHealth(), 1.f));
		}
	}
}