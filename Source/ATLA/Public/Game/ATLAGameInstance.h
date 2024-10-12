// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "ATLAGameInstance.generated.h"

/**
 *	ATLA Game Instance Class.
 */
UCLASS()
class ATLA_API UATLAGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Level")
	void GoToMainMenuLevel();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Level")
	void ExitToMainMenu();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Level")
	void ExitToDesktop();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Multiplayer")
	void CreateATLASession(ULocalPlayer* LocalPlayer);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Multiplayer")
	void DestroyATLASession();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Multiplayer")
	void FindATLASession(const FString& LobbyName);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Level")
	FString MainMenuLevelPath = FString(TEXT("/Game/ATLA/Maps/MainMenu_Level"));
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Level")
	FString TestingLevelPath = FString(TEXT("/Game/ATLA/Maps/Testing/Testing_Level"));
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Level")
	FString LobbyLevelPath = FString(TEXT("/Game/ATLA/Maps/Lobby_Level"));
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Level")
	bool bUseTestingLevel = true;

private:
	FString GetLevelPathToOpen();
};
