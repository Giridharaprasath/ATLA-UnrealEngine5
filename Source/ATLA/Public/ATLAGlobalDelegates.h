// Copyright Melon Studios.

#pragma once

#include "Delegates/DelegateCombinations.h"

#include "ATLAGlobalDelegates.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitSignature, bool, bIsSuccessfull);