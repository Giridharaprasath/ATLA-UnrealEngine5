// Copyright Melon Studios.

#include "AbilitySystem/ATLAAbilitySystemLibrary.h"
#include "ATLABlueprintFunctionLibrary.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ATLAGameplayAbility.h"
#include "Game/ATLAGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/ATLAHUD.h"
#include "Player/ATLAPlayerState.h"
#include "UI/WidgetController/ATLAWidgetController.h"
#include "Structure/FAbilityVisionLevel.h"

UPlayerHUDWidgetController* UATLAAbilitySystemLibrary::GetPlayerHUDWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AATLAHUD* ATLAHUD = Cast<AATLAHUD>(PC->GetHUD()))
		{
			AATLAPlayerState* PS = PC->GetPlayerState<AATLAPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetController WidgetController(PC, PS, ASC, AS);

			return ATLAHUD->GetPlayerHUDWidgetController(WidgetController);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UATLAAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AATLAHUD* ATLAHUD = Cast<AATLAHUD>(PC->GetHUD()))
		{
			AATLAPlayerState* PS = PC->GetPlayerState<AATLAPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetController WidgetController(PC, PS, ASC, AS);

			return ATLAHUD->GetAttributeMenuWidgetController(WidgetController);
		}
	}

	return nullptr;
}

void UATLAAbilitySystemLibrary::InitializeATLACharacterInfo(const UObject* WorldContextObject, ECharacterElement CharacterElement, ECharacterType CharacterType,
                                                            float Level, bool bIsPlayer, UAbilitySystemComponent* ASC)
{
	const AATLAGameMode* ATLAGameMode = Cast<AATLAGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ATLAGameMode == nullptr) return;

	const AActor* AvatarActor = ASC->GetAvatarActor();
	UATLACharacterInfo* ATLACharacterInfo = bIsPlayer ? ATLAGameMode->PlayerCharacterInfo : ATLAGameMode->EnemyCharacterInfo;

	const FCharacterInfo CharacterInfo = ATLACharacterInfo->GetCharacterInfo(CharacterElement, CharacterType);

	const TSubclassOf<UGameplayEffect> PrimaryAttribute = CharacterInfo.bUseCustomPrimaryAttributes
		                                                      ? CharacterInfo.PrimaryAttributes
		                                                      : ATLACharacterInfo->CommonPrimaryAttributes;

	const TSubclassOf<UGameplayEffect> SecondaryAttribute = CharacterInfo.bUseCustomSecondaryAttributes
		                                                        ? CharacterInfo.SecondaryAttributes
		                                                        : ATLACharacterInfo->CommonSecondaryAttributes;

	const TSubclassOf<UGameplayEffect> VitalAttribute = CharacterInfo.bUseCustomVitalAttributes
		                                                    ? CharacterInfo.VitalAttributes
		                                                    : ATLACharacterInfo->CommonVitalAttributes;

	if (PrimaryAttribute != nullptr)
	{
		ApplyGameplayEffectToTarget(PrimaryAttribute, ASC, AvatarActor, Level);
	}

	if (SecondaryAttribute != nullptr)
	{
		ApplyGameplayEffectToTarget(SecondaryAttribute, ASC, AvatarActor, Level);
	}

	if (VitalAttribute != nullptr)
	{
		ApplyGameplayEffectToTarget(VitalAttribute, ASC, AvatarActor, Level);
	}

	for (TSubclassOf Attribute : ATLACharacterInfo->CommonAttributes)
	{
		ApplyGameplayEffectToTarget(Attribute, ASC, AvatarActor, Level);
	}

	if (UATLAAbilitySystemComponent* ATLAASC = Cast<UATLAAbilitySystemComponent>(ASC))
	{
		ATLAASC->AddCharacterAbilities(ATLACharacterInfo->CommonAbilities, Level);
		ATLAASC->AddCharacterAbilities(CharacterInfo.CharacterAbilities, Level);

		ATLAASC->bStartupAbilitiesGiven = true;
		ATLAASC->AbilitiesGiven.Broadcast(ATLAASC);
	}
}

FAbilityVisionLevel UATLAAbilitySystemLibrary::GetAbilityVisionLevel(UDataTable* DataTable, const FName RowName)
{
	return *UATLABlueprintFunctionLibrary::GetDataTableRowByName<FAbilityVisionLevel>(DataTable, RowName);
}

void UATLAAbilitySystemLibrary::ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect>& Attribute, UAbilitySystemComponent* ASC, const AActor* AvatarActor, const int32 Level)
{
	FGameplayEffectContextHandle AttributeContextHandle = ASC->MakeEffectContext();
	AttributeContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle AttributeSpecHandle = ASC->MakeOutgoingSpec(Attribute, Level, AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToTarget(*AttributeSpecHandle.Data.Get(), ASC);
}
