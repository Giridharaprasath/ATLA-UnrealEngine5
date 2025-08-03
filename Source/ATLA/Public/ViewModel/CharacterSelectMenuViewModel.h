// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "CharacterSelectMenuViewModel.generated.h"

/**
 *	ATLA Character Select Menu UI View Model Class.
 */
UCLASS(BlueprintType)
class ATLA_API UCharacterSelectMenuViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	bool GetIsAirSelected() const;
	bool GetIsWaterSelected() const;
	bool GetIsEarthSelected() const;
	bool GetIsFireSelected() const;

	void SetIsAirSelected(const bool bNewIsAirSelected);
	void SetIsWaterSelected(const bool bNewIsWaterSelected);
	void SetIsEarthSelected(const bool bNewIsEarthSelected);
	void SetIsFireSelected(const bool bNewIsFireSelected);

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = SetIsAirSelected, Getter = GetIsAirSelected, Category = "ATLA|Character|Selection")
	bool bIsAirSelected;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = SetIsWaterSelected, Getter = GetIsWaterSelected, Category = "ATLA|Character|Selection")
	bool bIsWaterSelected;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = SetIsEarthSelected, Getter = GetIsEarthSelected, Category = "ATLA|Character|Selection")
	bool bIsEarthSelected;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = SetIsFireSelected, Getter = GetIsFireSelected, Category = "ATLA|Character|Selection")
	bool bIsFireSelected;
};
