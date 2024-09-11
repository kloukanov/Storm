#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class STORM_API ASpawner : public AActor
{
	GENERATED_BODY()

private:

	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEnemyBase>> EnemyClasses;

	class ASGameMode* GameMode;

	FTimerHandle SpawnEnemyTimerHandle;

	UPROPERTY(EditAnywhere)
	float SpawnRate = 2.f;
	
public:	
	ASpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:

	void SpawnEnemy();

};
