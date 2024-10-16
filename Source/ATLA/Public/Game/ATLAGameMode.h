// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/DataTable.h"

#include "ATLAGameMode.generated.h"

class AATLAPlayerController;

/**
 * ATLA Game Mode Class.
 */
UCLASS()
class ATLA_API AATLAGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// All Connected Player Controller Array
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ATLA")
	TArray<AATLAPlayerController*> ATLAPlayerControllers;

	UFUNCTION(BlueprintNativeEvent, Category = "Spawn")
	void SpawnSelectedCharacter(AATLAPlayerController* ATLAPlayerController, const FName CharacterName);

protected:
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Character Data")
	TObjectPtr<UDataTable> CharacterDataTable;
};
