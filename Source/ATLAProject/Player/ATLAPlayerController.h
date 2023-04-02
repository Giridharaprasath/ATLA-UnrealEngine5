// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATLAPlayerController.generated.h"

/**
 * ATLA Player Controller Class.
 */
UCLASS()
class ATLAPROJECT_API AATLAPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = "ATLA|HUD")
	void CreatePlayerHUD(const FText& CharacterName);
};