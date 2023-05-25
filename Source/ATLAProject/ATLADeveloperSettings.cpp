// Developed By Melon Studios.


#include "ATLADeveloperSettings.h"

UATLADeveloperSettings::UATLADeveloperSettings(const FObjectInitializer& obj) : EditorUIScale(1.0f)
{
	CategoryName = "ATLA";
	SectionName = "ATLA Settings";
}

void UATLADeveloperSettings::PostInitProperties()
{
	Super::PostInitProperties();

	if (!IsRunningCommandlet())
	{
		FSlateApplication::Get().SetApplicationScale(EditorUIScale);
	}
}

void UATLADeveloperSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == "EditorUIScale")
	{
		FSlateApplication::Get().SetApplicationScale(EditorUIScale);
	}
}