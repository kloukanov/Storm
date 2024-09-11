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

	// TODO: use a pool of enemies
	// basically mark enemies as dead and later unmark them and reset their locations
	if(GameMode->GetCurrentNumberOfEnemies() >= GameMode->MaxNumberOfEntities){
		UE_LOG(LogTemp, Warning, TEXT("maximum number of enemies already spawned"));
		return;
	}

	if(EnemyClasses.Num() > 0){
		int Index = FMath::RandRange(0, EnemyClasses.Num() - 1);
        GameMode->AddToEnemies(GetWorld()->SpawnActor<AEnemyBase>(EnemyClasses[Index], GetActorLocation(), GetActorRotation()));
	}
}