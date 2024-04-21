// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "ATLAHUD.generated.h"

class UATLAUserWidget;

/**
 * ATLA HUD Base Class.
 */
UCLASS()
class ATLA_API AATLAHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UATLAUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UATLAUserWidget> OverlayWidgetClass;
};
