// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

#include "ATLAGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedCharacterListSignature, const TArray<ECharacterElement>&,
                                            SelectedCharacters);

enum class ECharacterElement : uint8;

/**
 *	ATLA Game State Class.
 */
UCLASS()
class ATLA_API AATLAGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "ATLA|HUD")
	void MulticastCreateOtherPlayerInfoHUD();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "ATLA|Character")
	void ServerOnCharacterSelected(const ECharacterElement CharacterElement);

	bool CheckIsCharacterSelected(const ECharacterElement CharacterElement);

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Character")
	FOnSelectedCharacterListSignature OnCharacterSelected;

private:
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "ATLA|Character")
	void MulticastOnCharacterSelected(const ECharacterElement CharacterElement);

	UPROPERTY(EditDefaultsOnly, Category = "ATLA|Character")
	TMap<ECharacterElement, bool> SelectedCharacterList;
};
