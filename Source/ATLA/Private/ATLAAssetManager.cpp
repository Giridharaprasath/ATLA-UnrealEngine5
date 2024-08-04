// Copyright Melon Studios.

#include "ATLAAssetManager.h"
#include "ATLAGameplayTags.h"

UATLAAssetManager& UATLAAssetManager::Get()
{
	check(GEngine);

	UATLAAssetManager* ATLAAssetManager = Cast<UATLAAssetManager>(GEngine->AssetManager);
	return *ATLAAssetManager;
}

void UATLAAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FATLAGameplayTags::InitializeNativeGameplayTags();
}
