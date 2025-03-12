// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"

#include "WaitOnTick.generated.h"

class UCurveVector;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskTickDelegate, FVector, VisionVisible);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaskFinishedDelegate);

/**
 *	Wait On Tick Ability Task Class.
 */
UCLASS()
class ATLA_API UWaitOnTick : public UAbilityTask
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnTaskTickDelegate OnTaskTick;
	UPROPERTY(BlueprintAssignable)
	FOnTaskFinishedDelegate OnTaskFinished;

public:
	UWaitOnTick(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Ability Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UWaitOnTick* WaitOnTick(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration, UCurveVector* CurveVector);

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
 
private:
	bool bIsFinished;
	float TaskDuration;
	float TaskStartTime;
	float TaskEndTime;
	UPROPERTY()
	TObjectPtr<UCurveVector> TaskCurve;
};
