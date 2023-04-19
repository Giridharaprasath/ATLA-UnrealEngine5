// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "ATLAProject/ATLAProject.h"
#include "ATLAProject/Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"

#include "ATLACharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AATLACharacterBase*, Character);

class FObjectInitializer;
class UAbilitySystemComponent;
class UATLAAbilitySystemComponent;
class UCharacterAttributeSetBase;
class UATLAGameplayAbility;
class UGameplayEffect;

/*
 *  ATLA Character Base Class.
 */
UCLASS()
class ATLAPROJECT_API AATLACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AATLACharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintAssignable, Category = "ATLA|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "ATLA|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "ATLA|Character")
	virtual int32 GetAbilityLevel(EATLAAbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Character")
	virtual void FinishDying();
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character")
	FText GetCharacterName() const;

	// Getters for attributes from ATLAAttributeSetBase

	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	int32 GetCharacterLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetStamina() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetMaxStamina() const;
	
protected:

	TWeakObjectPtr<UATLAAbilitySystemComponent> ATLAAbilitySystemComponent;
	TWeakObjectPtr<UCharacterAttributeSetBase> CharacterAttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Abilities")
	TArray<TSubclassOf<UATLAGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attribute's Base Value.
	*/
	
	virtual void SetHealth(float Health);
	virtual void SetStamina(float Stamina);
};