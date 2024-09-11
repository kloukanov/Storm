#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "../HealthComponent.h"
#include "../AI/EnemyAIController.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if(HealthComponent){
		HealthComponent->OnActorDamaged.AddDynamic(this, &AEnemyBase::HandleTakeDamage);
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::HandleTakeDamage() {
	//TODO: play damaged animation
	UE_LOG(LogTemp, Warning, TEXT("this actor is taking damage: %s"), *this->GetActorNameOrLabel());
}

void AEnemyBase::ToggleIsDead(bool IsDead) {
	bIsDead = IsDead;

	SetActorHiddenInGame(bIsDead);
	SetActorEnableCollision(!bIsDead);

	if(bIsDead == false) {
		HealthComponent->ResetHealth();
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

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}