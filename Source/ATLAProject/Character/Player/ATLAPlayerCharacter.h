// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "ATLAProject/Character/ATLACharacterBase.h"
#include "ATLAProject/Player/ATLAPlayerState.h"
#include "ATLAProject/ATLAProject.h"

#include "ATLAPlayerCharacter.generated.h"

class FObjectInitializer;
class UInputAction;
class UATLAGameplayAbility;

/**
 * ATLA Player Character Class.
 */
UCLASS()
class ATLAPROJECT_API AATLAPlayerCharacter : public AATLACharacterBase
{
	GENERATED_BODY()

public:
	AATLAPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category = "ATLA|Abilities")
	void ActivateAbilityInputID(bool Activate, const EATLAAbilityID AbilityInputID);

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Abilities")
	TArray<TSubclassOf<UATLAGameplayAbility>> OwnedAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Input")
	UInputAction* IA_ConfirmAbility;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Input")
	UInputAction* IA_CancelAbility;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Input")
	UInputAction* IA_Ability_1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Input")
	UInputAction* IA_Ability_2;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Input")
	UInputAction* IA_Ability_3;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Input")
	UInputAction* IA_Ability_4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|AbilitySlot")
	TSubclassOf<UATLAGameplayAbility> Ability_1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|AbilitySlot")
	TSubclassOf<UATLAGameplayAbility> Ability_2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|AbilitySlot")
	TSubclassOf<UATLAGameplayAbility> Ability_3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|AbilitySlot")
	TSubclassOf<UATLAGameplayAbility> Ability_4;
	
protected:

	bool ASCInputBound = false;

	FGameplayTag DeadTag;
	
	virtual void OnRep_PlayerState() override; 
	
	void BindASCInput();

	void InitATLAAbilitySystemComponent(AATLAPlayerState* ATLAPlayerState);
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Abilities")
	void GiveNewAbility(TSubclassOf<UATLAGameplayAbility> AbilityClass);

private:
	void HandleInputPressesd_ConfirmAbility();
	void HandleInputPressed_CancelAbility();
	
	void HandleInputPressed_Ability_1();
	void HandleInputPressed_Ability_2();
	void HandleInputPressed_Ability_3();
	void HandleInputPressed_Ability_4();
	
	void HandleInputReleased_Ability_1();
	void HandleInputReleased_Ability_2();
	void HandleInputReleased_Ability_3();
	void HandleInputReleased_Ability_4();
};