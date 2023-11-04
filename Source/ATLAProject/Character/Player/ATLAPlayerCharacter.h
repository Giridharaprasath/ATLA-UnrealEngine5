// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "ATLAProject/Character/ATLACharacterBase.h"
#include "ATLAProject/Player/ATLAPlayerState.h"
#include "ATLAProject/ATLAProject.h"
#include "ATLAProject/Player/ATLAPlayerController.h"
#include "InputMappingContext.h"

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
	UInputMappingContext* IMC_PlayerInput;

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

	UFUNCTION(BlueprintGetter, Category = "ATLA")
	AATLAPlayerController* GetATLAPlayerController() { return ATLAPlayerController; }

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "ATLA")
	void ClientSetUpCharacter();
	
protected:

	bool ASCInputBound = false;

	FGameplayTag DeadTag;

	UPROPERTY(BlueprintGetter = GetATLAPlayerController, VisibleInstanceOnly, Category = "ATLA")
	AATLAPlayerController* ATLAPlayerController;
	
	virtual void OnRep_PlayerState() override; 
	
	void BindASCInput();

	void InitATLAAbilitySystemComponent(AATLAPlayerState* ATLAPlayerState);
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Abilities")
	void GiveNewAbility(TSubclassOf<UATLAGameplayAbility> AbilityClass);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "ATLA|Input")
	void ClientAddInputMapping();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "ATLA")
	void ClientSetCharacterName();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "ATLA")
	void ServerSaveCharacterName();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "ATLA|Discord")
	void ClientSetDiscordState();

private:
	void HandleInputPressed_ConfirmAbility();
	void HandleInputPressed_CancelAbility();
	
	void HandleInputPressed_Ability_1();
	void HandleInputPressed_Ability_2();
	void HandleInputPressed_Ability_3();
	void HandleInputPressed_Ability_4();
	
	void HandleInputReleased_Ability_1();
	void HandleInputReleased_Ability_2();
	void HandleInputReleased_Ability_3();
	void HandleInputReleased_Ability_4();

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|Player")
	void PlayerIsFalling();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|Player")
	void PlayerIsGrounded();
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "ATLA|Abilities")
	void ServerSetAbilityLevel(TSubclassOf<UATLAGameplayAbility> AbilityClass, int32 NewLevel);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "ATLA|Abilities|Debug")
	void GiveAllAbilitiesToPlayer();
};