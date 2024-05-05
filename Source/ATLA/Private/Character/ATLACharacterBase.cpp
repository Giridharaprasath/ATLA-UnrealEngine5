// Copyright Melon Studios.

#include "Character/ATLACharacterBase.h"

AATLACharacterBase::AATLACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AATLACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AATLACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AATLACharacterBase::InitAbilityActorInfo()
{
}
