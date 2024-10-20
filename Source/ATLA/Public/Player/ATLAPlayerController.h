// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "ATLAPlayerController.generated.h"

struct FGameplayTag;
class AATLAHUD;
class AATLAPlayerState;
class UInputMappingContext;
class UATLAInputConfig;
class UATLAAbilitySystemComponent;

/**
 * ATLA Player Controller Base Class.
 */
UCLASS()
class ATLA_API AATLAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AATLAPlayerController();

	UFUNCTION(Client, Reliable)
	void ClientOnPlayerJoined();

	UFUNCTION(Client, Reliable)
	void ClientOnPlayerLeft();

	UFUNCTION(BlueprintNativeEvent, Category = "ATLA|Player")
	void OnPlayerJoined();

	UFUNCTION(BlueprintNativeEvent, Category = "ATLA|Player")
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
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintGetter = GetATLAHUD, VisibleInstanceOnly, Category = "ATLA")
	AATLAHUD* ATLAHUD;

	UPROPERTY(BlueprintGetter = GetATLAPlayerState, VisibleInstanceOnly, Category = "ATLA")
	AATLAPlayerState* ATLAPlayerState;

private:

	UFUNCTION(Server, Reliable)
	void ServerSpawnSelectedPlayer(const FName CharacterName);
	
	UPROPERTY(EditAnywhere, Category = "ATLA|Input|Controls")
	TObjectPtr<UInputMappingContext> UIGenericControls;
	UPROPERTY(EditAnywhere, Category = "ATLA|Input|Controls")
	TObjectPtr<UInputMappingContext> ATLAPlayerControls;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "ATLA|Input")
	TObjectPtr<UATLAInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UATLAAbilitySystemComponent> ATLAAbilitySystemComponent;

	UATLAAbilitySystemComponent* GetATLAASC();
};
