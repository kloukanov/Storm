#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "SGameMode.h"
#include "Enemy/EnemyBase.h"
#include "TimerManager.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxComponent);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ASGameMode>(UGameplayStatics::GetGameMode(this));

	GetWorldTimerManager().SetTimer(SpawnEnemyTimerHandle, this, &ASpawner::SpawnEnemy, SpawnRate, true);

	if(HealthComponent){
		HealthComponent->OnActorDamaged.AddDynamic(this, &ASpawner::HandleTakeDamage);
	}
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnEnemy() {

	if(bIsActive == false){
		UE_LOG(LogTemp, Warning, TEXT("spawner is not active"));
		return;
	}

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

void ASpawner::HandleTakeDamage() {
	//TODO: play damaged animation
	UE_LOG(LogTemp, Warning, TEXT("this actor is taking damage: %s"), *this->GetActorNameOrLabel());
}

void ASpawner::HandleDestruction() {
	// TODO: create explosion??
	bIsActive = false;
	GetWorld()->GetTimerManager().ClearTimer(SpawnEnemyTimerHandle);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	// Destroy(); // might need this
}
