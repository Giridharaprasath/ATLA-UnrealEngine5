// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/UILoadingInterface.h"

#include "UILoadingComponent.generated.h"

class UATLALoadingWidget;

UCLASS(BlueprintType, ClassGroup=(UI), meta=(BlueprintSpawnableComponent))
class ATLA_API UUILoadingComponent : public UActorComponent, public IUILoadingInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI")
	void CreateLoadingWidgets();

#pragma region UI Loading Interface
	virtual void ShowBlurredLoadingPage() override;
	virtual void HideBlurredLoadingPage() override;
	virtual void ShowClearLoadingPage() override;
	virtual void HideClearLoadingPage() override;
#pragma endregion

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UATLALoadingWidget> LoadingWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UATLALoadingWidget> LoadingWidget;
};
