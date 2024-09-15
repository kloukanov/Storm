#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class STORM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ArmsMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ADSAimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwapToPrimaryGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwapToSecondaryGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseGameAction;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadAnimation;

	UPROPERTY(EditDefaultsOnly, Category = Gun)
	TArray<TSubclassOf<class AGunBase>> GunClasses;

	UPROPERTY(EditAnywhere, Category = Gun, meta = (AllowPrivateAccess = "true"))
	TArray<class AGunBase*> Guns;

	UPROPERTY()
	class AGunBase* Gun;

	class UAnimInstance* AnimInstance;

	FTimerHandle FireTimerHandle;

	bool bIsFiring = false; 

public:

	APlayerCharacter();

protected:

	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);

	void Look(const struct FInputActionValue& Value);

	void InitGuns();

	void Shoot();

	void StopShoot();

	void Fire();

	void Reload();

	void StartADSAim();

	void StopADSAim();

	class AGunBase* MakeGunAndSetActive(bool bSetActive, int GunIndex);

	void SwapToPrimaryGun();

	void SwapToSecondaryGun();

	void SwapGun(int Index);

	void ToggleGunActive(bool bIsActive);

	void PauseGame();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Blueprintcallable)
	FVector GetWeaponSocket() const;

	UFUNCTION(Blueprintcallable)
	void HandleTakeDamage();

	UFUNCTION(Blueprintcallable)
	void AddBulletRoundToGuns();

	UFUNCTION(Blueprintcallable)
	float GetHealthPercent() const;

	UFUNCTION(Blueprintcallable)
	FString GetBulletInMagCount() const;

	UFUNCTION(Blueprintcallable)
	FString GetBulletRoundsCount() const;
};
