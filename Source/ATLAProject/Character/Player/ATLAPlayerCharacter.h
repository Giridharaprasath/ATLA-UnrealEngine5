// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATLAProject/Character/ATLACharacterBase.h"
#include "ATLAProject/Player/ATLAPlayerState.h"
#include "ATLAPlayerCharacter.generated.h"

/**
 * ATLA Player Character Class
 */
UCLASS()
class ATLAPROJECT_API AATLAPlayerCharacter : public AATLACharacterBase
{
	GENERATED_BODY()

public:
	AATLAPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

protected:

	bool ASCInputBound = false;

	FGameplayTag DeadTag;
	
	virtual void OnRep_PlayerState() override; 
	
	void BindASCInput();

	void InitATLAAbilitySystemComponent(AATLAPlayerState* ATLAPlayerState);
};