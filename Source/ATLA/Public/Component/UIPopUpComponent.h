// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/UIPopUpInterface.h"

#include "UIPopUpComponent.generated.h"

/**
 *	ATLA UI Pop Up Component Class.	
 */
UCLASS(BlueprintType, ClassGroup=(UI), meta=(BlueprintSpawnableComponent))
class ATLA_API UUIPopUpComponent : public UActorComponent, public IUIPopUpInterface
{
	GENERATED_BODY()

public:
# pragma region Pop Up Interface
	virtual void ShowPopUpWidget(EUIPopUpWidget PopUpWidget) override;
	virtual void PopUpWidgetYes() override;
	virtual void PopUpWidgetNo() override;
# pragma endregion

	UFUNCTION(BlueprintCallable, Category="UI")
	void SetWidgetBase(UATLACommonUserWidget* Widget);

private:
	EUIPopUpWidget CurrentUIPopUpWidget;
	UPROPERTY()
	TObjectPtr<UATLACommonUserWidget> WidgetBase;
};
