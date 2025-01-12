// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "UI/Widget/ATLAUserWidget.h"

#include "ATLAPlayerHUD.generated.h"

class UPlayerHUDWidgetController;
class UAttributeSet;
struct FWidgetController;

/**
 *	ATLA Player HUD User Widget Class.
 */
UCLASS()
class ATLA_API UATLAPlayerHUD : public UATLAUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ATLA|HUD")
	void CreateOtherPlayerInfoWidget();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> OtherPlayerInfoVerticalBox;

private:
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UATLAUserWidget> OtherPlayerInfoWidgetClass;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UAttributeSet> AttributeSetClass;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UPlayerHUDWidgetController> PlayerHUDWidgetControllerClass;
};
