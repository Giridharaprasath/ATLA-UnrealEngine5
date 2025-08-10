// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/UICutsceneInterface.h"

#include "UICutsceneComponent.generated.h"

class UATLACutsceneWidget;

/**
 *	ATLA UI Cutscene Component Class.	
 */
UCLASS(BlueprintType, ClassGroup=(UI), meta=(BlueprintSpawnableComponent))
class ATLA_API UUICutsceneComponent : public UActorComponent, public IUICutsceneInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI")
	void CreateCutsceneWidgets();

#pragma region UI Cutscene Interface
	virtual void ShowCutsceneHorizontalBars() override;
	virtual void HideCutsceneHorizontalBars() override;
	virtual void ShowCutsceneVerticalBars() override;
	virtual void HideCutsceneVerticalBars() override;
#pragma endregion

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UATLACutsceneWidget> CutsceneBlackBarsWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UATLACutsceneWidget> CutsceneBlackBarsWidget;
};
