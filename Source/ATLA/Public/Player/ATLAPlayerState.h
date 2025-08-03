// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ATLAGlobalDelegates.h"

#include "ATLAPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
struct FSelectedCharacter;

/**
 * ATLA Player State Base Class.
 */
UCLASS()
class ATLA_API AATLAPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AATLAPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE FSelectedCharacter GetSelectedCharacter() const { return SelectedCharacter; }

	void SetCharacterElement(ECharacterElement InCharacterElement);

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Character")
	FOnCharacterSelectedSignature OnCharacterSelected;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level, Category = "ATLA|Player State")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SelectedCharacter, Category = "ATLA|Character")
	FSelectedCharacter SelectedCharacter;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_SelectedCharacter(FSelectedCharacter OldSelectedCharacter);
};
