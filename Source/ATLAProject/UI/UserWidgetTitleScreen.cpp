// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetTitleScreen.h"
#include "Components/TextBlock.h"
#include "OnlineSubsystem.h"

#include "ATLAProject/GameInstanceSubsystem/ATLAGameInstanceSubsystem.h" // * Header File to include ATLA GameInstance Subsystem

void UUserWidgetTitleScreen::NativeConstruct()
{
    Super::NativeConstruct();

    UGameInstance* GameInstance = GetGameInstance();
    if (GameInstance)
    {
        ATLAGISubsystem = GameInstance->GetSubsystem<UATLAGameInstanceSubsystem>();
    }
    if (ATLAGISubsystem)
    {
        FString PlayerName = ATLAGISubsystem->GetPlayerName();
        TextBlock_PlayerName->SetText(FText::FromString(*PlayerName));


    }
}
