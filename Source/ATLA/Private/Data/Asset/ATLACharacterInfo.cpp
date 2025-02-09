// Copyright Melon Studios.

#include "Data/Asset/ATLACharacterInfo.h"

FCharacterInfo UATLACharacterInfo::GetCharacterInfo(const ECharacterElement CharacterElement, const ECharacterType CharacterType)
{
	auto [Characters] = ATLACharacters.FindChecked(CharacterElement);
	return Characters.FindChecked(CharacterType);
}
