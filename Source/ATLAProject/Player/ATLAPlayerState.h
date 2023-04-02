// Fill out your copyright notice in the Description page of Project Settings.

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

	class UCharacterAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|ATLAPlayerState|Attributes")
	int32 GetCharacterLevel() const;

protected:

	UPROPERTY()
	UATLAAbilitySystemComponent* ATLAAbilitySystemComponent;

	UPROPERTY()
	UCharacterAttributeSetBase* CharacterAttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
	FDelegateHandle ManaChangeDelegateHandle;
	FDelegateHandle MaxManaChangeDelegateHandle;
	FDelegateHandle StaminaChangeDelegateHandle;
	FDelegateHandle MaxStaminaChangeDelegateHandle;
	FDelegateHandle CharacterLevelChangeDelegateHandle;

	virtual void BeginPlay() override;

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnManaChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnCharacterlevelChanged(const FOnAttributeChangeData& Data);

	virtual void OnStunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};