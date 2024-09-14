#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class STORM_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	float DamageAmount;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	float AttackRate;

	bool bIsDead;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	int SpawnPickupProbability = 1;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	USceneComponent* PickupSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class APickupBase>> PickupClasses;

	class UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackAnimation;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* GetHitAnimation;

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	void SpawnPickup();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();

	virtual void HandleTakeDamage();

	bool GetIsDead() const;

	float GetDamageAmount() const;

	float GetAttackRate() const;

	void ToggleIsDead(bool IsDead);
};
