// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ATLAProject/Player/ATLAPlayerController.h"

#include "ATLAGameMode.generated.h"

class AATLAPlayerController;

/**
 * ATLA Game Mode Class.
 */
UCLASS()
class ATLAPROJECT_API AATLAGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	// All Connected Player Controller Array
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ATLA")
	TArray<AATLAPlayerController*> ATLAPlayerControllers;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spawning")
	void SpawnSelectedCharacter(AATLAPlayerController* PlayerController, int32 PlayerIndex);

protected:

	// On New Player Joining
	virtual void OnPostLogin(AController* NewPlayer) override;

	// On Player Leaving
	virtual void Logout(AController* Exiting) override;
};