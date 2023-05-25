// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "ATLADeveloperSettings.generated.h"

/**
 * ATLA Developer Settings Class.
 */
UCLASS(Config = ATLASettings, meta = (DisplayName = "ATLA Developer Settings"))
class ATLAPROJECT_API UATLADeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UATLADeveloperSettings(const FObjectInitializer& obj);

	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(Config, EditAnywhere, meta = (ConfigRestartRequired = 1.0f, UIMin = 0.5f, UIMax = 2.0f))
	float EditorUIScale;
};