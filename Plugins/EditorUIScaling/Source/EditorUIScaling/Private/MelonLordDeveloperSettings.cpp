// Developed By Melon Studios.


#include "MelonLordDeveloperSettings.h"

UMelonLordDeveloperSettings::UMelonLordDeveloperSettings(const FObjectInitializer& obj) : EditorUIScale(1.0f)
{
	CategoryName = "General";
	SectionName = "Melon Lord";
}

void UMelonLordDeveloperSettings::PostInitProperties()
{
	Super::PostInitProperties();

	if (!IsRunningCommandlet())
	{
		FSlateApplication::Get().SetApplicationScale(EditorUIScale);
	}
}

#if WITH_EDITOR
void UMelonLordDeveloperSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == "EditorUIScale")
	{
		FSlateApplication::Get().SetApplicationScale(EditorUIScale);
	}
}
#endif