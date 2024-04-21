// Copyright Melon Studios.

#include "Actor/ATLAEffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ATLAAttributeSet.h"
#include "Components/BoxComponent.h"

AATLAEffectActor::AATLAEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	SetRootComponent(DefaultSceneComponent);
	
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(GetRootComponent());
}

void AATLAEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UATLAAttributeSet* ATLAAttributeSet = Cast<UATLAAttributeSet>(
			ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UATLAAttributeSet::StaticClass()));

		UATLAAttributeSet* MutableATLAAttributeSet = const_cast<UATLAAttributeSet*>(ATLAAttributeSet);
		MutableATLAAttributeSet->SetHealth(ATLAAttributeSet->GetHealth() + 25.f);
	}
}

void AATLAEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AATLAEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}
