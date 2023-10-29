// Developed By Melon Studios.


#include "ATLACheatManager.h"
#include "Kismet/GameplayStatics.h"
#include "ATLAProject/Character/Player/ATLAPlayerCharacter.h"

void UATLACheatManager::GivePlayerAllAbilities()
{
	AATLAPlayerCharacter* ATLAPlayerCharacter = Cast<AATLAPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (ATLAPlayerCharacter)
	{
		ATLAPlayerCharacter->GiveAllAbilitiesToPlayer();
	}
}

void UATLACheatManager::SetSprintAbilityLevel(int32 AbilityLevel)
{
	AATLAPlayerCharacter* ATLAPlayerCharacter = Cast<AATLAPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (ATLAPlayerCharacter)
	{
		ATLAPlayerCharacter->ServerSetAbilityLevel(Sprint, AbilityLevel);
	}
}

void UATLACheatManager::SetDodgeAbilityLevel(int32 AbilityLevel)
{
	AATLAPlayerCharacter* ATLAPlayerCharacter = Cast<AATLAPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (ATLAPlayerCharacter)
	{
		ATLAPlayerCharacter->ServerSetAbilityLevel(Dodge, AbilityLevel);
	}
}

void UATLACheatManager::SetVisionAbilityLevel(int32 AbilityLevel)
{
	AATLAPlayerCharacter* ATLAPlayerCharacter = Cast<AATLAPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (ATLAPlayerCharacter)
	{
		ATLAPlayerCharacter->ServerSetAbilityLevel(Vision, AbilityLevel);
	}
}

void UATLACheatManager::SetSeismicSenseAbilityLevel(int32 AbilityLevel)
{
	AATLAPlayerCharacter* ATLAPlayerCharacter = Cast<AATLAPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (ATLAPlayerCharacter)
	{
		ATLAPlayerCharacter->ServerSetAbilityLevel(SeismicSense, AbilityLevel);
	}
}