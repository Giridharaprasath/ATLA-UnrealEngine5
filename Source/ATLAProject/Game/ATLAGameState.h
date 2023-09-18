// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

#include "ATLAGameState.generated.h"

/**
 * ATLA Game State Class.
 */
UCLASS()
class ATLAPROJECT_API AATLAGameState : public AGameState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "ATLA|Discord")
	void MulticastSetDiscordPartySize();
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "ATLA")
	void MulticastCreateTeamHUD();
};