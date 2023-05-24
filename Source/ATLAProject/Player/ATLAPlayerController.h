// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "ATLAPlayerController.generated.h"

class AATLAHUD;
class AATLAGameState;
class AATLAPlayerState;

/**
 * ATLA Player Controller Class.
 */
UCLASS()
class ATLAPROJECT_API AATLAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(Server, Reliable, Category = "ATLA|HUD")
	void ServerCreateTeamHUD();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void OpenPauseMenu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void OpenInteractionUI(bool bOpenInteractionUI);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void OpenPlayerMenu();

	UFUNCTION(BlueprintGetter, Category = "ATLA")
	AATLAHUD* GetATLAHUD() { return ATLAHUD; }

	UFUNCTION(BlueprintGetter, Category = "ATLA")
	AATLAGameState* GetATLAGameState() { return ATLAGameState; }

	UFUNCTION(BlueprintGetter, Category = "ATLA")
	AATLAPlayerState* GetATLAPlayerState() { return ATLAPlayerState; }

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "ATLA")
	void ClientSpawnPlayer(int32 PlayerIndex);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "ATLA")
	void ServerSpawnPlayer(AATLAPlayerController* ATLAPlayerController, int32 PlayerIndex);
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "ATLA|HUD")
	void CreatePlayerHUD(const FText& CharacterName);

	UPROPERTY(BlueprintGetter = GetATLAHUD, VisibleInstanceOnly, Category = "ATLA")
	AATLAHUD* ATLAHUD;

	UPROPERTY(BlueprintGetter = GetATLAGameState, VisibleInstanceOnly, Category = "ATLA")
	AATLAGameState* ATLAGameState;

	UPROPERTY(BlueprintGetter = GetATLAPlayerState, VisibleInstanceOnly, Category = "ATLA")
	AATLAPlayerState* ATLAPlayerState;
};