// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATLAEffectActor.generated.h"

class USceneComponent;
class UBoxComponent;

/**
 * ATLA Effect Actor Class.
 */
UCLASS()
class ATLA_API AATLAEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AATLAEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;
};
