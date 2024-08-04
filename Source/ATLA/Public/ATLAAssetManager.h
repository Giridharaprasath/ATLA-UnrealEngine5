// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "ATLAAssetManager.generated.h"

/**
 * ATLA Asset Manager Class.
 */
UCLASS()
class ATLA_API UATLAAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UATLAAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
