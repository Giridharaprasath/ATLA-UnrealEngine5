// Copyright Melon Studios.

#include "AbilitySystem/AbilityTasks/WaitOnTick.h"
#include "Curves/CurveVector.h"

UWaitOnTick::UWaitOnTick(const FObjectInitializer& ObjectInitializer)
{
	bTickingTask = true;
}

UWaitOnTick* UWaitOnTick::WaitOnTick(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration,
                                     UCurveVector* CurveVector)
{
	UWaitOnTick* MyObj = NewAbilityTask<UWaitOnTick>(OwningAbility);

	MyObj->TaskDuration = FMath::Max(Duration, 0.01f);
	MyObj->TaskCurve = CurveVector;
	MyObj->TaskStartTime = MyObj->GetWorld()->GetTimeSeconds();
	MyObj->TaskEndTime = MyObj->TaskStartTime + Duration;

	return MyObj;
}

void UWaitOnTick::Activate()
{
	Super::Activate();
}

void UWaitOnTick::TickTask(float DeltaTime)
{
	if (bIsFinished)
	{
		return;
	}

	Super::TickTask(DeltaTime);

	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime >= TaskEndTime)
	{
		bIsFinished = true;

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnTaskFinished.Broadcast();
		}
		EndTask();
		return;
	}

	const FVector CurveValue = TaskCurve->GetVectorValue(CurrentTime - TaskStartTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTaskTick.Broadcast(CurveValue);
	}
}
