// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAPlayerController.h"
#include "ATLAPlayerState.h"
#include "AbilitySystemComponent.h"

void AATLAPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();

	if (ATLAPlayerState)
	{
		ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, InPawn);
	}
}