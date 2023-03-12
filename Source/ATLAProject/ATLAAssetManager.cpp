// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAAssetManager.h"
#include "AbilitySystemGlobals.h"

void UATLAAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
