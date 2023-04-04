// Developed By Melon Studios.

#include "ATLAHUD.h"

FString AATLAHUD::GetGameName()
{
	FString GameName;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectName"),
		GameName,
		GGameIni);
	return GameName;
}

FString AATLAHUD::GetGameVersion()
{
	FString GameVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		GameVersion,
		GGameIni);
	return GameVersion;
}

FString AATLAHUD::GetCompanyName()
{
	FString CompanyName;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("CompanyName"),
		CompanyName,
		GGameIni);
	return CompanyName;
}