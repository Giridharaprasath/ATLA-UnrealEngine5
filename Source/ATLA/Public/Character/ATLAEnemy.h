// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Character/ATLACharacterBase.h"

#include "ATLAEnemy.generated.h"

/**
 * ATLA Enemy Character Base Class.
 */
UCLASS()
class ATLA_API AATLAEnemy : public AATLACharacterBase
{
	GENERATED_BODY()

public:
	AATLAEnemy();

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface **/

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
