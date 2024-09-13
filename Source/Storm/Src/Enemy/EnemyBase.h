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

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack() {};

	UFUNCTION(Blueprintcallable)
	void HandleTakeDamage();

	bool GetIsDead() const;

	float GetDamageAmount() const;

	float GetAttackRate() const;

	void ToggleIsDead(bool IsDead);
};
