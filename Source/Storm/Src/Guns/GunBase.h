#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class STORM_API AGunBase : public AActor
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	float FireRange;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	bool bIsAutomatic = false;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	float FireSpeed;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	int MaxMagSize;

	int CurrentMagSize;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	int MaxBulletRounds;

	int CurrentBulletRounds;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ADSCameraComponent;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadAnimation;

public:	
	AGunBase();

	bool PullTrigger();

	bool TryReloadGun();

	bool GetIsAutomatic() const { return bIsAutomatic; }

	float GetFireSpeed() const { return FireSpeed; }

	void AddBulletRound();

	int GetCurrentMagSize() const { return CurrentMagSize; }

	int GetCurrentBulletRounds() const { return CurrentBulletRounds; }

	int GetMaxBulletRounds() const { return MaxBulletRounds; }

	UAnimMontage* GetFireAnimation() const { return FireAnimation; }

	UAnimMontage* GetReloadAnimation() const { return ReloadAnimation; }

protected:
	virtual void BeginPlay() override;

	bool GunTrace(FHitResult& OutHit, FVector& OutShotDirection);

public:	
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetMesh() const;
};
