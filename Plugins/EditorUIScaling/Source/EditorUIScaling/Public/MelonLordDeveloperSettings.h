// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "MelonLordDeveloperSettings.generated.h"

/**
 * Melon Lord Developer Settings Class.
 */
UCLASS(Config = EditorSettings, meta = (DisplayName = "Melon Lord Developer Settings"))
class EDITORUISCALING_API UMelonLordDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UMelonLordDeveloperSettings(const FObjectInitializer& obj);

	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(Config, EditAnywhere, meta = (DisplayName = "Editor UI Scale", ConfigRestartRequired = 1.0f, UIMin = 0.5f, UIMax = 2.0f), Category = "General")
	float EditorUIScale;
};