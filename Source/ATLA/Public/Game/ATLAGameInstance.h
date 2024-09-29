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

private:
	UPROPERTY(EditDefaultsOnly, Category = "ATLA|Level")
	const TSoftObjectPtr<UWorld> MainMenuLevel;
	UPROPERTY(EditAnywhere, Category = "ATLA|Level")
	const TSoftObjectPtr<UWorld> TestingLevel;
	UPROPERTY(EditAnywhere, Category = "ATLA|Level")
	const TSoftObjectPtr<UWorld> LobbyLevel;
	UPROPERTY(EditAnywhere, Category = "ATLA|Level")
	bool bUseTestingLevel{true};
};
