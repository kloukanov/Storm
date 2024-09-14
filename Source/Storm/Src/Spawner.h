#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class STORM_API ASpawner : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEnemyBase>> EnemyClasses;

	class ASGameMode* GameMode;

	FTimerHandle SpawnEnemyTimerHandle;

	UPROPERTY(EditAnywhere)
	float SpawnRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Spawner Properties", meta = (AllowPrivateAccess = "true"))
	bool bIsActive;
	
public:	
	ASpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetIsActive(bool IsActive);

	bool GetIsActive() const { return bIsActive; }

	void HandleDestruction();

	UFUNCTION(Blueprintcallable)
	void HandleTakeDamage();

private:

	void SpawnEnemy();

};
