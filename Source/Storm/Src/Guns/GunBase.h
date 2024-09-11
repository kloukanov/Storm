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
	bool IsAutomatic = false;

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
	
	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ADSCameraComponent;

public:	
	AGunBase();

	bool PullTrigger();

	bool TryReloadGun();

protected:
	virtual void BeginPlay() override;

	bool GunTrace(FHitResult& OutHit, FVector& OutShotDirection);

public:	
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetMesh() const;
};
