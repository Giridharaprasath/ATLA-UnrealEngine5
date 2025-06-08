// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "ATLAGlobalDelegates.h"
#include "GameFramework/HUD.h"
#include "Interface/UIPopUpInterface.h"
#include "UI/WidgetController/ATLAWidgetController.h"

#include "ATLAHUD.generated.h"

class UATLACommonActivatableUserWidget;
class UATLAPlayerHUD;
class UATLACommonActivatableWidget;
class UATLACommonUserWidget;
class UPlayerHUDWidgetController;
class UAttributeMenuWidgetController;
struct FWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UUIPopUpComponent;

/**
 * ATLA HUD Base Class.
 */
UCLASS()
class ATLA_API AATLAHUD : public AHUD
{
	GENERATED_BODY()

public:
	AATLAHUD();

	UPROPERTY()
	UUIPopUpComponent* UIPopUpComponent;
	
	UPlayerHUDWidgetController* GetPlayerHUDWidgetController(const FWidgetController& WidgetController);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetController& WidgetController);

	void CreatePlayerHUDWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	void CreateOtherPlayerInfoHUD() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void OpenPauseMenu();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void OpenAttributesMenu();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void OpenCharacterSelectUIWidget();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void CloseCharacterSelectUIWidget();

	UPROPERTY(BlueprintAssignable, Category = "ATLA|HUD")
	FOnInitSignature OnHUDInit;

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|HUD")
	bool bHUDInitialized = false;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "ATLA|HUD")
	void CreatePlayerUIBaseWidget();

private:
	UPROPERTY(BlueprintReadOnly, meta = ( AllowPrivateAccess = true ), Category = "ATLA|HUD")
	TObjectPtr<UATLAPlayerHUD> PlayerHUDWidget;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UATLAPlayerHUD> PlayerHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerHUDWidgetController> PlayerHUDWidgetController;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UPlayerHUDWidgetController> PlayerHUDWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	UPROPERTY(BlueprintReadOnly, meta = ( AllowPrivateAccess = true ), Category = "ATLA|HUD")
	TObjectPtr<UATLACommonUserWidget> PlayerUIWidgetBase;
	UPROPERTY(EditAnywhere, Category = "ATLA|UI|Widget Base")
	TSubclassOf<UATLACommonUserWidget> PlayerUIWidgetBaseClass;

	UPROPERTY(EditAnywhere, Category = "ATLA|HUD|Pause Menu")
	TSubclassOf<UATLACommonActivatableWidget> PauseMenuWidget;

	UPROPERTY(EditAnywhere, Category = "ATLA|HUD|Attributes Menu")
	TSubclassOf<UATLACommonActivatableUserWidget> AttributesMenuWidget;

	UPROPERTY(EditAnywhere, Category = "ATLA|HUD|Character Select")
	TSubclassOf<UATLACommonActivatableWidget> CharacterSelectWidget;
};
