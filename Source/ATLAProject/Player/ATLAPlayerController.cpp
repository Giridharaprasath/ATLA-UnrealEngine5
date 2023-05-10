// Developed By Melon Studios.

#include "ATLAPlayerController.h"
#include "ATLAPlayerState.h"
#include "ATLAProject/HUD/ATLAHUD.h"
#include "AbilitySystemComponent.h"
#include "ATLAProject/Game/ATLAGameState.h"
#include "Kismet/GameplayStatics.h"
//#include "ATLAProject/Character/Player/ATLAPlayerCharacter.h"

void AATLAPlayerController::ServerCreateTeamHUD_Implementation()
{
	AATLAGameState* GameState = Cast<AATLAGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
		GameState->MulticastCreateTeamHUD();
	}
}

void AATLAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalPlayerController())
	{
		return;
	}

	ATLAHUD = GetHUD<AATLAHUD>();
	ATLAGameState = Cast<AATLAGameState>(UGameplayStatics::GetGameState(GetWorld()));
	ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
}

void AATLAPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ATLAPlayerState)
	{
		ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, InPawn);
	}
}

void AATLAPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ServerCreateTeamHUD();
	
	Super::EndPlay(EndPlayReason);
}

void AATLAPlayerController::CreatePlayerHUD(const FText& CharacterName)
{
	if (!IsLocalPlayerController())
	{
		return;
	}
	
	//AATLAPlayerCharacter* ATLAPlayerCharacter = GetPawn<AATLAPlayerCharacter>();
	
	if (ATLAHUD)
	{
		ATLAHUD->CreatePlayerHUD();

		if (ATLAPlayerState)
		{
			ATLAHUD->SetPlayerHealthBar(ATLAPlayerState->GetHealth() / FMath::Max(ATLAPlayerState->GetMaxHealth(), 1.f));
		}
		
		/*if (ATLAPlayerCharacter)
		{
			ATLAHUD->SetCharacterName(ATLAPlayerCharacter->GetCharacterName());
		}*/

		ATLAHUD->SetCharacterName(CharacterName);
	}

	ServerCreateTeamHUD();
}