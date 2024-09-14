#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../HealthComponent.h"
#include "../AI/EnemyAIController.h"
#include "../Pickups/PickupBase.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	PickupSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	PickupSpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Speed;

	if(HealthComponent){
		HealthComponent->OnActorDamaged.AddDynamic(this, &AEnemyBase::HandleTakeDamage);
	}

	AnimInstance = GetMesh()->GetAnimInstance();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::Attack() {
	if(AnimInstance && AttackAnimation){
		AnimInstance->Montage_Play(AttackAnimation, 1.f);
	}
}

void AEnemyBase::SpawnPickup() {

	int Probability = FMath::RandRange(0, SpawnPickupProbability);

	if(Probability == 0) {
		FVector SpawnLocation = PickupSpawnPoint->GetComponentLocation();

		if(PickupClasses.Num() > 0){
			int Index = FMath::RandRange(0, PickupClasses.Num() - 1);
			GetWorld()->SpawnActor<APickupBase>(PickupClasses[Index], SpawnLocation, FRotator::ZeroRotator);
		}
	}
}

void AEnemyBase::HandleTakeDamage() {
	UE_LOG(LogTemp, Warning, TEXT("this actor is taking damage: %s"), *this->GetActorNameOrLabel());
	if(AnimInstance && GetHitAnimation) {
		AnimInstance->Montage_Play(GetHitAnimation, 1.f);
	}
}

void AEnemyBase::ToggleIsDead(bool IsDead) {
	if(IsDead) {
		bIsDead = true;
		SpawnPickup();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}else {
		bIsDead = false;
		HealthComponent->ResetHealth();
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
	/* 

	// possible optimization for later

	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if(AIController != nullptr){

		if(bIsDead) {
			// TODO: unpossess?
			// AIController->UnPossess();
		}
		else {
			// TODO: possess again?
			// AIController->Possess(this);
		}
	}
	*/
}

bool AEnemyBase::GetIsDead() const { return bIsDead; }

float AEnemyBase::GetDamageAmount() const { return DamageAmount; }

float AEnemyBase::GetAttackRate() const { return AttackRate; }

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}