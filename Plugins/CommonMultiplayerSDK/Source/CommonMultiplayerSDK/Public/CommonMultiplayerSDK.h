// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "CommonMultiplayerSDK.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCommonMultiplayerSDK, Log, All);

USTRUCT(BlueprintType)
struct FSessionSettingsInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUseLan = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NumberOfPlayers = 4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bAllowJoinInProgress = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bAllowJoinViaPresenceFriendsOnly = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bAllowInvites = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUsesPresence = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsDedicated = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUsesStats = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bAllowJoinViaPresence = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUseLobbiesIfAvailable = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bShouldAdvertise = true;
};

class FCommonMultiplayerSDKModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
