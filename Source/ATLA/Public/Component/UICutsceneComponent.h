// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/UICutsceneInterface.h"

#include "UICutsceneComponent.generated.h"

class UATLACutsceneWidget;

UCLASS(BlueprintType, ClassGroup=(UI), meta=(BlueprintSpawnableComponent))
class ATLA_API UUICutsceneComponent : public UActorComponent, public IUICutsceneInterface
{
	GENERATED_BODY()

public:
	void CreateCutsceneWidgets();

#pragma region UI Cutscene Interface
	virtual void ShowCutsceneBlackBars() override;
	virtual void HideCutsceneBlackBars() override;
#pragma endregion

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UATLACutsceneWidget> CutsceneHorizontalBarsWidgetClass;

private:
	TObjectPtr<UATLACutsceneWidget> CutsceneHorizontalBarsWidget;
};
