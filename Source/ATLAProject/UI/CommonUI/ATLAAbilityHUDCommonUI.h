// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"

#include "ATLAAbilityHUDCommonUI.generated.h"

/**
 *	ATLA Ability HUD Common Activatable Widget UI Class 
 */
UCLASS()
class ATLAPROJECT_API UATLAAbilityHUDCommonUI : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ATLA|UI")
	void ShowResetBinding();
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI")
	void HideResetBinding();

	UFUNCTION(BlueprintImplementableEvent, Category = "ATLA|UI")
	void HandleResetAction();
	
protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle ResetInputActionData;

	FUIActionBindingHandle ResetHandle;
};