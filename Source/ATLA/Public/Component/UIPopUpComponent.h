// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/UIPopUpInterface.h"

#include "UIPopUpComponent.generated.h"

UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATLA_API UUIPopUpComponent : public UActorComponent, public IUIPopUpInterface
{
	GENERATED_BODY()

public:
	/** UI Pop Up Interface **/
	virtual void ShowPopUpWidget(EUIPopUpWidget PopUpWidget) override;
	virtual void PopUpWidgetYes() override;
	virtual void PopUpWidgetNo() override;
	/** End UI Pop Up Interface **/

	UFUNCTION(BlueprintCallable, Category="UI")
	void SetWidgetBase(UATLACommonUserWidget* Widget);

private:
	EUIPopUpWidget CurrentUIPopUpWidget;
	TObjectPtr<UATLACommonUserWidget> WidgetBase;
};
