// Copyright Melon Studios.

#include "Game/ATLAGameMode.h"
#include "Character/ATLAPlayer.h"
#include "Player/ATLAPlayerController.h"
#include "ATLABlueprintFunctionLibrary.h"
#include "ATLA/ATLA.h"
#include "Structure/FATLACharacters.h"

void AATLAGameMode::SpawnSelectedCharacter_Implementation(AATLAPlayerController* ATLAPlayerController,
                                                          const FName CharacterName)
{
	UE_LOG(LogATLA, Display, TEXT("GM : On Spawn Selected Character Name: %s For %s"), *CharacterName.ToString(),
	       *ATLAPlayerController->GetName());

	if (APawn* Pawn = ATLAPlayerController->GetPawn(); Pawn != nullptr)
	{
		Pawn->Destroy();
	}

	const FATLACharacters Row = UATLABlueprintFunctionLibrary::GetCharacterData(CharacterDataTable, CharacterName);

	FActorSpawnParameters PlayerSpawnParameters;
	PlayerSpawnParameters.Owner = ATLAPlayerController;

	const AActor* PlayerStart = FindPlayerStart(ATLAPlayerController, Row.CharacterName);

	AATLAPlayer* SpawnCharacter = GetWorld()->SpawnActor<AATLAPlayer>(Row.CharacterClass, PlayerStart->GetTransform(),
	                                                                  PlayerSpawnParameters);
	ATLAPlayerController->Possess(SpawnCharacter);
	SpawnCharacter->ClientSetUpCharacter();
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

	ATLAPlayerControllers.Remove(ExitingATLAPlayerController);

	for (const auto PC : ATLAPlayerControllers)
	{
		PC->ClientOnPlayerLeft();
	}
}
