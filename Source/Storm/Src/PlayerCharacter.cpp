#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Guns/GunBase.h"
#include "SPlayerController.h"
#include "HealthComponent.h"
#include "SGameMode.h"

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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = ArmsMesh->GetAnimInstance();

	if(HealthComponent){
		HealthComponent->OnActorDamaged.AddDynamic(this, &APlayerCharacter::HandleTakeDamage);
	}
	
	InitGuns();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::InitGuns() {

	if(Gun){
		// we already have a gun
		return;
	}

	// add primary gun to gun inventory array
	Guns.Add(MakeGunAndSetActive(true, 0));

	// secondary gun
	Guns.Add(MakeGunAndSetActive(false, 1));
}

// TODO: a little unsafe asking for index of gun class array
AGunBase* APlayerCharacter::MakeGunAndSetActive(bool bSetActive, int GunIndex) {

	// check if safe
	if(GunIndex > GunClasses.Num() - 1){
		UE_LOG(LogTemp, Warning, TEXT("gun index passed in is not valid, GunIndex: %d, GunClasses length: %d"), GunIndex, (GunClasses.Num() - 1));
		return nullptr;
	}

	AGunBase* AGun = GetWorld()->SpawnActor<AGunBase>(GunClasses[GunIndex]);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AGun->AttachToComponent(ArmsMesh, AttachmentRules, TEXT("GripPoint"));
	AGun->SetOwner(this);

	if(bSetActive ==  true) {
		Gun = AGun;
	}else {
		AGun->SetActorHiddenInGame(true);
		AGun->SetActorEnableCollision(false);
	}

	return AGun;
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
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerCharacter::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopShoot);

		EnhancedInputComponent->BindAction(ADSAimAction, ETriggerEvent::Started, this, &APlayerCharacter::StartADSAim);
		EnhancedInputComponent->BindAction(ADSAimAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopADSAim);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Reload);
		
		EnhancedInputComponent->BindAction(SwapToPrimaryGunAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SwapToPrimaryGun);
		EnhancedInputComponent->BindAction(SwapToSecondaryGunAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SwapToSecondaryGun);

		EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PauseGame);
	}
}

void APlayerCharacter::Shoot() {
	if(Gun && Gun->GetFireAnimation() && !bIsFiring){
		bIsFiring = true;
		Fire();
		if(Gun->GetIsAutomatic()) {
			GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &APlayerCharacter::Fire, Gun->GetFireSpeed(), true);
		}
	}
}

void APlayerCharacter::StopShoot() {
	if (bIsFiring) {
		bIsFiring = false;
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	}
}

void APlayerCharacter::Fire() {
	if(AnimInstance && AnimInstance->GetCurrentActiveMontage() != Gun->GetReloadAnimation()){
		if(Gun->PullTrigger()){
			AnimInstance->Montage_Play(Gun->GetFireAnimation(), 1.f);		
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
		// if we are not playing reload anim
		if (AnimInstance && AnimInstance->GetCurrentActiveMontage() != Gun->GetReloadAnimation()) {
			ASPlayerController* PlayerController = Cast<ASPlayerController>(GetWorld()->GetFirstPlayerController());
			if(PlayerController){
				PlayerController->SetViewTargetWithBlend(Gun, 0.15f);
			}
		}
	}
}

void APlayerCharacter::StopADSAim() {
	if(Gun) {
		ASPlayerController* PlayerController = Cast<ASPlayerController>(GetWorld()->GetFirstPlayerController());
		if(PlayerController){
			PlayerController->SetViewTargetWithBlend(this, 0.15f);
		}
	}
}

void APlayerCharacter::Reload() {
	if(Gun && Gun->GetReloadAnimation()){
		if (AnimInstance) {
			// first change to FPS camera in case we are ADSing
			ASPlayerController* PlayerController = Cast<ASPlayerController>(GetWorld()->GetFirstPlayerController());
			if(PlayerController){
				PlayerController->SetViewTargetWithBlend(this, 0.15f);
			}

			if(Gun->TryReloadGun()){
				AnimInstance->Montage_Play(Gun->GetReloadAnimation(), 1.f);
			}else {
				// TODO: failed to reload, show some sort of indication 
			}
		}
	}
}

void APlayerCharacter::SwapGun(int Index) {
	if(Guns.Num() == 2) {
		if(Gun && Guns[Index] != nullptr && Guns[Index]->IsHidden() == true){
			// make current gun hidden
			ToggleGunActive(false);
			if(AnimInstance){
				StopShoot();
				StopADSAim();
				AnimInstance->Montage_Play(Gun->GetReloadAnimation(), 5.f);
				Gun = Guns[Index];
				ToggleGunActive(true);
			}
		}
	}else {
		UE_LOG(LogTemp, Warning, TEXT("Guns inventory is not 2"));
	}
}

void APlayerCharacter::SwapToPrimaryGun() {
	bPrimaryWeaponEquipped = true;
	SwapGun(0);
}

void APlayerCharacter::SwapToSecondaryGun() {
	bPrimaryWeaponEquipped = false;
	SwapGun(1);
}

void APlayerCharacter::AddBulletRoundToGuns() {
	// TODO:: add the round for all guns
	if(Gun){
		Gun->AddBulletRound();
	}
}


FString APlayerCharacter::GetBulletInMagCount() const {
	if(Gun){
		return FString::FromInt(Gun->GetCurrentMagSize());
	}
	return "";
}


FString APlayerCharacter::GetBulletRoundsCount() const {
	if(Gun){
		return FString::FromInt(Gun->GetCurrentBulletRounds()) + "/" + FString::FromInt(Gun->GetMaxBulletRounds());
	}
	return "";
}

// probably move to Gun class
void APlayerCharacter::ToggleGunActive(bool bIsActive) {
	if(Gun){
		Gun->SetActorHiddenInGame(!bIsActive);
		Gun->SetActorEnableCollision(bIsActive);
	}
}

void APlayerCharacter::HandleTakeDamage() {
	//TODO: play damaged animation
	UE_LOG(LogTemp, Warning, TEXT("this actor is taking damage: %s"), *this->GetActorNameOrLabel());
}

void APlayerCharacter::HandlePlayerDied() {
	//TODO: play death anim
}

float APlayerCharacter::GetHealthPercent() const {
	return HealthComponent->GetHealthPercent();
}

void APlayerCharacter::PauseGame() {
	ASGameMode *GM = GetWorld()->GetAuthGameMode<ASGameMode>();
	if(GM){
		if(GM->IsGamePaused()){
			// GM->PlayGame();
		}else {
			GM->ShowPauseScreen();
		}
	}
}

FVector APlayerCharacter::GetWeaponSocket() const {
	if(Gun){
		return Gun->GetMesh()->GetSocketLocation(TEXT("leftHandSocket"));
	}
	return FVector::ZeroVector;
}