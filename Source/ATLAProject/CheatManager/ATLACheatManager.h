// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"

#include "ATLACheatManager.generated.h"

class UATLAGameplayAbility;

/**
 * ATLA Cheat Manager Class.
 */
UCLASS()
class ATLAPROJECT_API UATLACheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Abilities")
	TSubclassOf<UATLAGameplayAbility> Sprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Abilities")
	TSubclassOf<UATLAGameplayAbility> Dodge;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Abilities")
	TSubclassOf<UATLAGameplayAbility> Vision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Abilities|Earth")
	TSubclassOf<UATLAGameplayAbility> SeismicSense;

	UFUNCTION(Exec)
	void GivePlayerAllAbilities();

	UFUNCTION(Exec)
	void SetSprintAbilityLevel(int32 AbilityLevel);

	UFUNCTION(Exec)
	void SetDodgeAbilityLevel(int32 AbilityLevel);

	UFUNCTION(Exec)
	void SetVisionAbilityLevel(int32 AbilityLevel);

	UFUNCTION(Exec)
	void SetSeismicSenseAbilityLevel(int32 AbilityLevel);
};
