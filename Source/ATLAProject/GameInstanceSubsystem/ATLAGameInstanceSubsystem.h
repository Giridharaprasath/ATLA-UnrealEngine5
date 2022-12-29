// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "ATLAGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ATLAPROJECT_API UATLAGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UATLAGameInstanceSubsystem();

	UFUNCTION(BlueprintCallable)
	static bool HasOnlineSubsystem(FName Subsystem);

private:
	IOnlineSessionPtr SessionInterface;
};
