// Copyright Melon Studios.

#include "Character/ATLAPlayer.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/ATLAHUD.h"
#include "Input/ATLAInputComponent.h"
#include "Player/ATLAPlayerController.h"
#include "Player/ATLAPlayerState.h"

AATLAPlayer::AATLAPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AATLAPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// * Init Ability Actor Info for the Sever
	InitAbilityActorInfo();
}

void AATLAPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// * Init Ability Actor Info for the Client
	InitAbilityActorInfo();
}

int32 AATLAPlayer::GetPlayerLevel()
{
	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	check(ATLAPlayerState);

	return ATLAPlayerState->GetPlayerLevel();
}

void AATLAPlayer::ClientSetUpCharacter_Implementation()
{
	OnCharacterSelected();
}

void AATLAPlayer::OnCharacterSelected_Implementation()
{
}

void AATLAPlayer::InitAbilityActorInfo()
{
	AATLAPlayerState* ATLAPlayerState = GetPlayerState<AATLAPlayerState>();
	check(ATLAPlayerState);

	ATLAPlayerState->SetCharacterElement(CharacterElement);

	ATLAPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ATLAPlayerState, this);
	Cast<UATLAAbilitySystemComponent>(ATLAPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = ATLAPlayerState->GetAbilitySystemComponent();
	AttributeSet = ATLAPlayerState->GetAttributeSet();

	// TODO : FIND ANOTHER METHOD TO INIT PLAYER HUD
	if (AATLAPlayerController* ATLAPlayerController = Cast<AATLAPlayerController>(GetController()))
	{
		if (AATLAHUD* ATLAHUD = Cast<AATLAHUD>(ATLAPlayerController->GetHUD()))
		{
			ATLAHUD->CreatePlayerHUDWidget(ATLAPlayerController, ATLAPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();

	const UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	SetMovementModeTag(MovementComponent->MovementMode, MovementComponent->CustomMovementMode, true);
}

void AATLAPlayer::InitializeDefaultAttributes() const
{
	if (!HasAuthority()) return;

	UATLAAbilitySystemLibrary::InitializeATLACharacterInfo(this, CharacterElement, CharacterType, 1.f, true, GetAbilitySystemComponent());
}

void AATLAPlayer::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
}

void AATLAPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UATLAInputComponent* ATLAInputComponent = Cast<UATLAInputComponent>(PlayerInputComponent))
	{
		ATLAInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::MoveATLAPlayer);
		ATLAInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::LookATLAPlayer);
	}
}

void AATLAPlayer::MoveATLAPlayer(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AATLAPlayer::LookATLAPlayer(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}
