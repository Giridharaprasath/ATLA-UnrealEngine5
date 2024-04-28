// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATLAEffectActor.generated.h"

class UGameplayEffect;
/**
 * ATLA Effect Actor Class.
 */
UCLASS()
class ATLA_API AATLAEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AATLAEffectActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category = "ATLA|Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
