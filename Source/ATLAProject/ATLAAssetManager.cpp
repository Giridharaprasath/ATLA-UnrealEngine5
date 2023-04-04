// Developed By Melon Studios.

#include "ATLAAssetManager.h"
#include "AbilitySystemGlobals.h"

void UATLAAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}