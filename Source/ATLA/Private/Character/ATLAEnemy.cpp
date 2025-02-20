// Copyright Melon Studios.

#include "Character/ATLAEnemy.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAbilitySystemLibrary.h"
#include "AbilitySystem/ATLAAttributeSet.h"

AATLAEnemy::AATLAEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

	InitializeDefaultAttributes();
}

void AATLAEnemy::InitializeDefaultAttributes() const
{
	UATLAAbilitySystemLibrary::InitializeATLACharacterInfo(this, CharacterElement, CharacterType, 1.f, false,
	                                                       GetAbilitySystemComponent());
}
