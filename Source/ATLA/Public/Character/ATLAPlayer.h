// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Character/ATLACharacterBase.h"

#include "ATLAPlayer.generated.h"

/**
 * ATLA Player Character Base Class.
 */
UCLASS()
class ATLA_API AATLAPlayer : public AATLACharacterBase
{
	GENERATED_BODY()

public:
	AATLAPlayer();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface **/

	UFUNCTION(Client, Reliable)
	void ClientSetUpCharacter();
	
	UFUNCTION(BlueprintNativeEvent, Category = "ATLA|Character")
	void OnCharacterSelected();
	
protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
};
