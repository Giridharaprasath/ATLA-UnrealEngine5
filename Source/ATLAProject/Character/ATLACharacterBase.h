// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "ATLAProject/ATLAProject.h"
#include "ATLAProject/Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "ATLACharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AATLACharacterBase*, Character);

UCLASS()
class ATLAPROJECT_API AATLACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AATLACharacterBase(const class FObjectInitializer& ObjectInitializer);

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
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

	// Getters for attributes from ATLAAttributeSetBase

	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	int32 GetCharacterLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetMana() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetMaxMana() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetStamina() const;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Character|Attributes")
	float GetMaxStamina() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UATLAAbilitySystemComponent> ATLAAbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSetBase> CharacterAttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ATLA|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Abilities")
	TArray<TSubclassOf<class UATLAGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attribute's Base Value.
	*/
	
	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);
	virtual void SetStamina(float Stamina);
};