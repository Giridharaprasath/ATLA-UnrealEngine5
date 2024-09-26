// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "ATLAPlayerController.generated.h"

class AATLAHUD;
class AATLAPlayerState;
class UInputMappingContext;

/**
 * ATLA Player Controller Base Class.
 */
UCLASS()
class ATLA_API AATLAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AATLAPlayerController();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Player")
	void OnPlayerJoined();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Player")
	void OnPlayerLeft();

	UFUNCTION(BlueprintGetter, Category = "ATLA")
	AATLAHUD* GetATLAHUD() { return ATLAHUD; }

	UFUNCTION(BlueprintGetter, Category = "ATLA")
	AATLAPlayerState* GetATLAPlayerState() { return ATLAPlayerState; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void OpenPauseMenu();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "ATLA|Character")
	void ClientSpawnSelectedPlayer(const FName CharacterName);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintGetter = GetATLAHUD, VisibleInstanceOnly, Category = "ATLA")
	AATLAHUD* ATLAHUD;

	UPROPERTY(BlueprintGetter = GetATLAPlayerState, VisibleInstanceOnly, Category = "ATLA")
	AATLAPlayerState* ATLAPlayerState;

private:

	UFUNCTION(Server, Reliable)
	void ServerSpawnSelectedPlayer(const FName CharacterName);
	
	UPROPERTY(EditAnywhere, Category = "ATLA|Controls")
	TObjectPtr<UInputMappingContext> UIGenericControls;
	UPROPERTY(EditAnywhere, Category = "ATLA|Controls")
	TObjectPtr<UInputMappingContext> ATLAPlayerControls;
};
