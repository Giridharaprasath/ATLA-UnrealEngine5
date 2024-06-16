// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "ATLAAttributeSet.generated.h"

// * Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties()
	{
	}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * ATLA Attribute Set Class.
 */
UCLASS()
class ATLA_API UATLAAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UATLAAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Define all the common Attribute Set for all the Characters

	/**
	 *	Primary Attributes
	 **/

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Primary", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Primary", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Primary", ReplicatedUsing = OnRep_Resilience)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, Resilience)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Primary", ReplicatedUsing = OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, Vigor)

	/**
	 *	Secondary Attributes
	 **/

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, ArmorPenetration)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, BlockChance)
	
	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, CriticalHitChance)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, CriticalHitDamage)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, CriticalHitResistance)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, HealthRegeneration)

	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_StaminaRegeneration)
	FGameplayAttributeData StaminaRegeneration;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, StaminaRegeneration)
	
	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Secondary", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, MaxStamina)

	/**
	 *	Vital Attributes
	 **/

	// Current Health, Capped by Max Health.
	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Vital", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, Health)

	// Current Stamina, Capped by Max Stamina.
	UPROPERTY(BlueprintReadOnly, Category = "ATLA|AttributeSet|Vital", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UATLAAttributeSet, Stamina)

	// On Rep Function for all the Attribute Sets
	
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	
	UFUNCTION()
	virtual void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
	UFUNCTION()
	virtual void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	virtual void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	virtual void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	virtual void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	virtual void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	virtual void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	virtual void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	virtual void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const;

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
