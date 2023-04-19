// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "CharacterAttributeSetBase.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Character Attribute Set Base Class for all the Characters.
 */
UCLASS()
class ATLAPROJECT_API UCharacterAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Define all the common Attribute Set for all the Characters

	// Current Health, Capped by Max Health.
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Health)

	// Maximum Health for the Character.
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MaxHealth)

	// Health regeneration rate for the Character
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Health", ReplicatedUsing = OnRep_HealthRegenRate)
	FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, HealthRegenRate)
	
	// Current Stamina, Capped by Max Stamina.
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Stamina", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Stamina)
	
	// Maximum Mana for the Character.
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Stamina", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MaxStamina)

	// Stamina Regeneration rate for the Character.
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Stamina", ReplicatedUsing = OnRep_StaminaRegenRate)
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, StaminaRegenRate)

	// Current Character Level.
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Level", ReplicatedUsing = OnRep_CharacterLevel)
	FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, CharacterLevel)

	// Meta Attributes
	
	// Damage done to the Character, Temporary value that only exists on the Server.
	UPROPERTY(BlueprintReadOnly, Category = "AttributeSet|Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Damage)

	// On Rep Function for all the Attribute Sets
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate);
	
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	UFUNCTION()
	virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate);

	UFUNCTION()
	virtual void OnRep_CharacterLevel(const FGameplayAttributeData& OldCharacterLevel);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Attribute Set Overrides
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};