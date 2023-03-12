// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EATLAAbilityID : uint8
{
	// 0 None
	None UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel UMETA(DisplayName = "Cancel"),
	// 3 Jump
	Jump UMETA(DisplayName = "Jump"),
	//4 Sprint
	Sprint UMETA(DisplayName = "Sprint")
};