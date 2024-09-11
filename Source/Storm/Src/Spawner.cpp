#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "SGameMode.h"
#include "Enemy/EnemyBase.h"
#include "TimerManager.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	// Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ASGameMode>(UGameplayStatics::GetGameMode(this));

	GetWorldTimerManager().SetTimer(SpawnEnemyTimerHandle, this, &ASpawner::SpawnEnemy, SpawnRate, true);
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnEnemy() {
	if(GameMode->GetCurrentNumberOfSpawnedEnemies() >= GameMode->MaxNumberOfEntities){
		UE_LOG(LogTemp, Warning, TEXT("maximum number of enemies already spawned"));

		// look if we can reuse a dead enemy
		AEnemyBase* Enemy = GameMode->GetADeadEnemy();
		if(Enemy) {
			// reusing dead enemies and making them alive again lol
			Enemy->ToggleIsDead(false);
			Enemy->SetActorLocation(GetActorLocation());
			Enemy->SetActorRotation(GetActorRotation());
			UE_LOG(LogTemp, Warning, TEXT("spawned a reused enemy!"));
		}

		UE_LOG(LogTemp, Warning, TEXT("didn't spawn a reused enemy"));
		return;
	}

	if(EnemyClasses.Num() > 0){
		int Index = FMath::RandRange(0, EnemyClasses.Num() - 1);
        GameMode->AddToEnemies(GetWorld()->SpawnActor<AEnemyBase>(EnemyClasses[Index], GetActorLocation(), GetActorRotation()));
	}
}