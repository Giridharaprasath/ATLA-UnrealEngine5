// Copyright Melon Studios.

#include "Game/ATLAGameMode.h"
#include "Character/ATLAPlayer.h"
#include "Player/ATLAPlayerController.h"
#include "ATLABlueprintFunctionLibrary.h"
#include "ATLA/ATLA.h"
#include "Game/ATLAGameState.h"
#include "Structure/FATLACharacters.h"

void AATLAGameMode::SpawnSelectedCharacter_Implementation(AATLAPlayerController* ATLAPlayerController, const ECharacterElement CharacterElement)
{
	const FString CharacterName = UATLABlueprintFunctionLibrary::GetCharacterElementString(CharacterElement);

	AATLAGameState* ATLAGameState = GetGameState<AATLAGameState>();

	if (ATLAGameState->CheckIsCharacterSelected(CharacterElement))
	{
		ATLAPlayerController->ClientOnCharacterSelected(false, CharacterElement);
		return;
	}

	ATLAGameState->ServerOnCharacterSelected(CharacterElement);

	UE_LOG(LogATLA, Display, TEXT("GM : On Spawn Selected Character Name: %s For %s"), *CharacterName,
	       *ATLAPlayerController->GetName());

	if (APawn* Pawn = ATLAPlayerController->GetPawn(); Pawn != nullptr)
	{
		Pawn->Destroy();
	}

	// TODO : ADD LOGIC TO DESELECT THE CHARACTER WHEN SWITCHING CHARACTER.
	// IS SWITCHING CHARACTER ALLOWED?

	const FATLACharacters Row = UATLABlueprintFunctionLibrary::GetCharacterData(CharacterDataTable, FName(*CharacterName));

	FActorSpawnParameters PlayerSpawnParameters;
	PlayerSpawnParameters.Owner = ATLAPlayerController;

	const AActor* PlayerStart = FindPlayerStart(ATLAPlayerController, Row.CharacterName);

	AATLAPlayer* SpawnCharacter = GetWorld()->SpawnActor<AATLAPlayer>(Row.CharacterClass, PlayerStart->GetTransform(), PlayerSpawnParameters);
	ATLAPlayerController->Possess(SpawnCharacter);
	SpawnCharacter->ClientSetUpCharacter();

	ATLAPlayerController->ServerSetSelectedCharacter(true, CharacterElement);
	ATLAPlayerController->ClientOnCharacterSelected(true, CharacterElement);
}

void AATLAGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AATLAPlayerController* NewATLAPlayerController = Cast<AATLAPlayerController>(NewPlayer);

	ATLAPlayerControllers.Add(NewATLAPlayerController);

	for (const auto PC : ATLAPlayerControllers)
	{
		PC->ClientOnPlayerJoined();
	}
}

void AATLAGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AATLAPlayerController* ExitingATLAPlayerController = Cast<AATLAPlayerController>(Exiting);
	if (ExitingATLAPlayerController->SelectedCharacter.bIsSelected)
	{
		AATLAGameState* ATLAGameState = GetGameState<AATLAGameState>();
		ATLAGameState->ServerOnCharacterDeselected(
			ExitingATLAPlayerController->SelectedCharacter.CharacterElement);
	}

	ATLAPlayerControllers.Remove(ExitingATLAPlayerController);

	for (const auto PC : ATLAPlayerControllers)
	{
		PC->ClientOnPlayerLeft();
	}
}
