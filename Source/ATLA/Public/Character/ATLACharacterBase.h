// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Enum/ECharacterElement.h"
#include "Interface/ATLAPlayerInterface.h"
#include "Interface/CombatInterface.h"

#include "ATLACharacterBase.generated.h"

class UATLAAbilitySystemComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

/**
 * ATLA Character Base Class.
 */
UCLASS(Abstract)
class ATLA_API AATLACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface, public IATLAPlayerInterface
{
	GENERATED_BODY()

public:
	AATLACharacterBase(const FObjectInitializer& ObjectInitializer);

	UATLAAbilitySystemComponent* GetATLAAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	/** ATLA Player Interface Functions START **/
	virtual ECharacterElement GetCharacterElement() const override;
	virtual ECharacterType GetCharacterType() const override;
	/** ATLA Player Interface Functions END **/
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Character")
	FText CharacterName;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();
	virtual void InitializeDefaultAttributes() const;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	void SetMovementModeTag(EMovementMode MovementMode, uint8 CustomMovementMode, bool bTagEnabled) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Character")
	ECharacterElement CharacterElement;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ATLA|Character")
	ECharacterType CharacterType;
};
