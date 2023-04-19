// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"

#include "ATLAPlayerState.generated.h"

class UAbilitySystemComponent;
class UATLAAbilitySystemComponent;
class UCharacterAttributeSetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealth, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, bool, bCharacterSelected);

/**
 * ATLA Player State Class.
 */
UCLASS()
class ATLAPROJECT_API AATLAPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AATLAPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UCharacterAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	int32 GetCharacterLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character")
	FText GetCharacterName() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|Character")
	void SetCharacterName(FText NewCharacterName);
	
	UFUNCTION()
	virtual void OnRep_CharacterName(const FText OldCharacterName);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY()
	UATLAAbilitySystemComponent* ATLAAbilitySystemComponent;

	UPROPERTY()
	UCharacterAttributeSetBase* CharacterAttributeSetBase;

	FGameplayTag DeadTag;
	
	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
	FDelegateHandle StaminaChangeDelegateHandle;
	FDelegateHandle MaxStaminaChangeDelegateHandle;
	FDelegateHandle CharacterLevelChangeDelegateHandle;

	virtual void BeginPlay() override;
	
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnCharacterlevelChanged(const FOnAttributeChangeData& Data);

	virtual void OnStunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|Character", ReplicatedUsing = OnRep_CharacterName)
	FText CharacterName;

	// Custom Delegates
	
	UPROPERTY(BlueprintAssignable, Category = "ATLA|ATLAPlayerState")
	FOnHealth OnHealth;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Character")
	FOnCharacterSelected OnCharacterSelected;
};