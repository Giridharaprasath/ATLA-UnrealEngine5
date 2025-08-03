// Copyright Melon Studios.

#pragma once

#include "Delegates/DelegateCombinations.h"
#include "Structure/FSelectedCharacter.h"

#include "ATLAGlobalDelegates.generated.h"

enum class ECharacterElement : uint8;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitSignature, bool, bIsSuccessfull);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelectedSignature, FSelectedCharacter, SelectedCharacter);