// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "ATLAGlobalDelegates.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "ATLAPlayerController.generated.h"

class AATLAHUD;
class AATLAPlayerState;
class UInputMappingContext;
class UATLAInputConfig;
class UATLAAbilitySystemComponent;
enum class ECharacterElement : uint8;

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
	FORCEINLINE AATLAHUD* GetATLAHUD() const { return ATLAHUD; }

	UFUNCTION(BlueprintGetter, Category = "ATLA")
	FORCEINLINE AATLAPlayerState* GetATLAPlayerState() const { return ATLAPlayerState; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	bool GetShowCharacterSelectMenuAtStart();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "ATLA|Character")
	void ServerOnCharacterSelected(const ECharacterElement CharacterElement);

	UFUNCTION(Server, Reliable)
	void ServerSetSelectedCharacter(const bool bIsSuccessful, const ECharacterElement CharacterElement);

	UFUNCTION(Client, Reliable)
	void ClientOnCharacterSelected(const bool bIsSuccessful, const ECharacterElement CharacterElement);

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Character")
	FOnCharacterSelectedSignature OnCharacterSelected;

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|Character")
	FSelectedCharacter SelectedCharacter;

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "ATLA|HUD")
	void ClientCreateOtherPlayerInfoHUD();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void OpenPauseMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void OpenAttributesMenu();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "ATLA|HUD")
	void ServerCreateOtherPlayerInfoHUD();

private:
	UPROPERTY(BlueprintGetter = GetATLAHUD, VisibleInstanceOnly, Category = "ATLA")
	AATLAHUD* ATLAHUD;

	UPROPERTY(BlueprintGetter = GetATLAPlayerState, VisibleInstanceOnly, Category = "ATLA")
	AATLAPlayerState* ATLAPlayerState;

	UFUNCTION()
	void OnHUDInitialized(bool bIsSuccessful);

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

	UPROPERTY(EditAnywhere, Category = "ATLA|Character|Selection")
	bool bAlwaysShowCharacterSelectMenu;
};
