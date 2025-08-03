// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Structure/FSelectedCharacter.h"

#include "ATLAGameState.generated.h"

enum class ECharacterElement : uint8;
class UCharacterSelectMenuViewModel;

/**
 *	ATLA Game State Class.
 */
UCLASS()
class ATLA_API AATLAGameState : public AGameState
{
	GENERATED_BODY()

public:
	AATLAGameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintGetter, Category = "ATLA|Character|Selection")
	FORCEINLINE UCharacterSelectMenuViewModel* GetCharacterSelectMenuViewModel() const { return CharacterSelectMenuViewModel; }

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "ATLA|HUD")
	void MulticastCreateOtherPlayerInfoHUD();

	bool CheckIsCharacterSelected(const ECharacterElement CharacterElement) const;
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "ATLA|Character")
	void ServerOnCharacterSelected(const ECharacterElement CharacterElement);
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "ATLA|Character")
	void ServerOnCharacterDeselected(const ECharacterElement CharacterElement);

private:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SelectedCharacterInfo, Category = "ATLA|Character|Selection")
	TArray<FSelectedCharacter> SelectedCharacterInfo;

	UFUNCTION()
	void OnRep_SelectedCharacterInfo();

	void CreateCharacterSelectMenuViewModel();
	void SetSelectedCharacterInViewModel();

	UPROPERTY(BlueprintGetter = GetCharacterSelectMenuViewModel, Category = "ATLA|Character|Selection")
	TObjectPtr<UCharacterSelectMenuViewModel> CharacterSelectMenuViewModel;
	UPROPERTY(EditAnywhere, Category = "ATLA|Character|Selection")
	TSubclassOf<UCharacterSelectMenuViewModel> CharacterSelectMenuViewModelClass;
};
