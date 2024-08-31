// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "ATLAPlayerController.generated.h"

class UInputMappingContext;

/**
 * ATLA Player Controller Base Class.
 */
UCLASS()
class ATLA_API AATLAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AATLAPlayerController();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Player")
	void OnPlayerJoined();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|Player")
	void OnPlayerLeft();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "ATLA|Controls")
	TObjectPtr<UInputMappingContext> ATLAPlayerControls;
};
