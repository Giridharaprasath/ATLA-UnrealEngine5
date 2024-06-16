// Copyright Melon Studios.

#include "Character/ATLAEnemy.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAttributeSet.h"

AATLAEnemy::AATLAEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UATLAAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UATLAAttributeSet>("AttributeSet");
}

int32 AATLAEnemy::GetPlayerLevel()
{
	return Level;
}

void AATLAEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AATLAEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UATLAAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
