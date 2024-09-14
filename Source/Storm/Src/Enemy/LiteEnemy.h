#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "LiteEnemy.generated.h"

UCLASS()
class STORM_API ALiteEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	ALiteEnemy();

protected:

	virtual void BeginPlay() override;

	virtual void Attack() override;

public:

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Blueprintcallable)
	virtual void HandleTakeDamage() override;
};
