// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ATLAGameplayAbility.h"

#include "ATLAGameplayAbility_Jump.generated.h"

/**
 *	ATLA Gameplay Ability Jump Class.
 */
UCLASS()
class ATLA_API UATLAGameplayAbility_Jump : public UATLAGameplayAbility
{
	GENERATED_BODY()

public:
	UATLAGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                                const FGameplayTagContainer* SourceTags = nullptr,
	                                const FGameplayTagContainer* TargetTags = nullptr,
	                                FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable, Category = "ATLA|Abilities")
	void CharacterJumpStart();
	UFUNCTION(BlueprintCallable, Category = "ATLA|Abilities")
	void CharacterJumpStop();
};
