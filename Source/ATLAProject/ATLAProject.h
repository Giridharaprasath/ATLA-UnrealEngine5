// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, Category = "ATLA|AbilityInputID")
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
	// 4 Sprint
	Sprint UMETA(DisplayName = "Sprint"),
	// 5 Glide
	Glide UMETA(DisplayName = "Glide"),
	// 6 Dodge
	Dodge UMETA(DisplayName = "Dodge"),
	// 7 Can Do Abilities
	CanDoAbilities UMETA(DisplayName = "CanDoAbilities"),
	// 8 Ability
	Ability UMETA(DisplayName = "Ability"),

	/*
	 *  AIR ABILITIES
	 */
	// AIR BALL
	AirBall UMETA(DisplayName = "Air Ball"),

	/*
	 *  WATER ABILITIES
	 */
	Heal UMETA(DisplayName = "Heal"),

	/*
	 *  EARTH ABILITIES
	 */
	// SEISMIC SENSE
	SeismicSense UMETA(DisplayName = "Seismic Sense"),

	/*
	 *  FIRE ABILITIES
	 */
	// TORCH
	Torch UMETA(DisplayName = "Torch")
};