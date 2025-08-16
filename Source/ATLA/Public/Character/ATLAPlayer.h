// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Character/ATLACharacterBase.h"

#include "ATLAPlayer.generated.h"

class URadarComponent;
struct FInputActionValue;
class UInputAction;

/**
 * ATLA Player Character Base Class.
 */
UCLASS()
class ATLA_API AATLAPlayer : public AATLACharacterBase
{
	GENERATED_BODY()

public:
	AATLAPlayer(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Radar")
	URadarComponent* RadarComponent;

#pragma region Combat Interface
	virtual int32 GetPlayerLevel() override;
#pragma endregion

	UFUNCTION(Client, Reliable)
	void ClientSetUpCharacter();

	UFUNCTION(BlueprintNativeEvent, Category = "ATLA|Character")
	void OnCharacterSelected();

protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveATLAPlayer(const FInputActionValue& Value);
	void LookATLAPlayer(const FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly, Category = "ATLA|Input")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "ATLA|Input")
	UInputAction* LookAction;
};
