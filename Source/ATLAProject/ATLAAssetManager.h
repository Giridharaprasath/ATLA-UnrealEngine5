// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "ATLAAssetManager.generated.h"

/**
 * ATLA Asset Manager Class.
 */
UCLASS()
class ATLAPROJECT_API UATLAAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;
};