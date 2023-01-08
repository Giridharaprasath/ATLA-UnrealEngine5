// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UserWidgetTitleScreen.generated.h"

/**
 * 
 */
UCLASS()
class ATLAPROJECT_API UUserWidgetTitleScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_PlayerName;

	UPROPERTY()
	class UATLAGameInstanceSubsystem* ATLAGISubsystem;
};
