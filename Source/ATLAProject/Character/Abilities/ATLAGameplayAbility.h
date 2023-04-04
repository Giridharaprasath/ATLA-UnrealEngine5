// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ATLAProject/ATLAProject.h"

#include "ATLAGameplayAbility.generated.h"

/**
 * ATLA Gameplay Ability Class.
 */
UCLASS()
class ATLAPROJECT_API UATLAGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UATLAGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Ability")
	EATLAAbilityID AbilityInputID = EATLAAbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Ability")
	EATLAAbilityID AbilityID = EATLAAbilityID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Ability")
	bool ActiveAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};