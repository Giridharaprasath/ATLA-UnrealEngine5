// Copyright Melon Studios.

#include "Game/ATLAGameMode.h"
#include "ATLA/ATLA.h"
#include "Character/ATLAPlayer.h"
#include "Player/ATLAPlayerController.h"

void AATLAGameMode::SpawnSelectedCharacter_Implementation(AATLAPlayerController* ATLAPlayerController,
                                                          int32 PlayerIndex)
{
	UE_LOG(LogATLA, Display, TEXT("GM : On Spawn Selected Character Index: %i For %s"), PlayerIndex,
	       *ATLAPlayerController->GetName());

	if (APawn* Pawn = ATLAPlayerController->GetPawn(); Pawn != nullptr)
	{
		Pawn->Destroy();
	}
	
	if (const FATLACharacters* Row = GetDataTableRowByName<FATLACharacters>(CharacterDataTable, FName(*FString::FromInt(PlayerIndex)));
		Row != nullptr)
	{
		FActorSpawnParameters PlayerSpawnParameters;
		PlayerSpawnParameters.Owner = ATLAPlayerController;

		const AActor* PlayerStart = FindPlayerStart(ATLAPlayerController, Row->CharacterName);
	
		AATLAPlayer* SpawnCharacter = GetWorld()->SpawnActor<AATLAPlayer>(Row->CharacterClass, PlayerStart->GetTransform(), PlayerSpawnParameters);
		ATLAPlayerController->Possess(SpawnCharacter);
	}
}

void AATLAGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AATLAPlayerController* NewATLAPlayerController = Cast<AATLAPlayerController>(NewPlayer);

	ATLAPlayerControllers.Add(NewATLAPlayerController);

	NewATLAPlayerController->OnPlayerJoined();
}

void AATLAGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AATLAPlayerController* ExitingATLAPlayerController = Cast<AATLAPlayerController>(Exiting);

	ATLAPlayerControllers.Remove(ExitingATLAPlayerController);

	ExitingATLAPlayerController->OnPlayerLeft();
}
