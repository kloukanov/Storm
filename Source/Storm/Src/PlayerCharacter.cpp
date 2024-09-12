#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Guns/GunBase.h"
#include "SPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	// ArmsMesh->SetOnlyOwnerSee(true);
	ArmsMesh->SetupAttachment(FirstPersonCameraComponent);
	ArmsMesh->bCastDynamicShadow = false;
	ArmsMesh->CastShadow = false;
	ArmsMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = ArmsMesh->GetAnimInstance();
	
	
	PickUpGun();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::PickUpGun() {

	if(Gun){
		// we already have a gun
		return;
	}

	Gun = GetWorld()->SpawnActor<AGunBase>(GunClass);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Gun->AttachToComponent(ArmsMesh, AttachmentRules, TEXT("GripPoint"));
	Gun->SetOwner(this);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// locomotion
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// shooting and aim
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);
		EnhancedInputComponent->BindAction(ADSAimAction, ETriggerEvent::Started, this, &APlayerCharacter::StartADSAim);
		EnhancedInputComponent->BindAction(ADSAimAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopADSAim);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Reload);
	}
}

void APlayerCharacter::Shoot() {
	if(Gun && FireAnimation){
		if(Gun->PullTrigger()){
			if (AnimInstance && AnimInstance->IsAnyMontagePlaying() == false) {
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::StartADSAim() {
	if(Gun){
		// if we are not playing any anims
		if (AnimInstance && AnimInstance->IsAnyMontagePlaying() == false) {
			ASPlayerController* PlayerController = Cast<ASPlayerController>(GetWorld()->GetFirstPlayerController());
			if(PlayerController){
				PlayerController->SetViewTargetWithBlend(Gun, 0.15f);
			}
		}
	}
}

void APlayerCharacter::StopADSAim() {
	if(Gun){
		// if we are not playing any anims
			ASPlayerController* PlayerController = Cast<ASPlayerController>(GetWorld()->GetFirstPlayerController());
			if(PlayerController){
				PlayerController->SetViewTargetWithBlend(this, 0.15f);
			}
	}
}

void APlayerCharacter::Reload() {
	if(Gun && ReloadAnimation){
		if (AnimInstance && AnimInstance->IsAnyMontagePlaying() == false) {
			// first change to FPS camera in case we are ADSing
			ASPlayerController* PlayerController = Cast<ASPlayerController>(GetWorld()->GetFirstPlayerController());
			if(PlayerController){
				PlayerController->SetViewTargetWithBlend(this, 0.15f);
			}

			if(Gun->TryReloadGun()){
				AnimInstance->Montage_Play(ReloadAnimation, 1.f);
			}else {
				// TODO: failed to reload, show some sort of indication 
			}
		}
	}
}

FVector APlayerCharacter::GetWeaponSocket() const {
	if(Gun){
		return Gun->GetMesh()->GetSocketLocation(TEXT("leftHandSocket"));
	}
	return FVector::ZeroVector;
}