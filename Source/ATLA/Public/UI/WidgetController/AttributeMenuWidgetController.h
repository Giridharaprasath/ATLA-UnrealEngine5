// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ATLAWidgetController.h"

#include "AttributeMenuWidgetController.generated.h"

struct FATLAAttributeInfo;
class UAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FATLAAttributeInfo&, Info);

/**
 *	Attribute Menu Widget Controller Class.
 */
UCLASS(BlueprintType, Blueprintable)
class ATLA_API UAttributeMenuWidgetController : public UATLAWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
