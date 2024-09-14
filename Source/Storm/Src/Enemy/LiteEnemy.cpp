#include "LiteEnemy.h"
#include "../HealthComponent.h"

ALiteEnemy::ALiteEnemy() {
}

void ALiteEnemy::BeginPlay() {
	Super::BeginPlay();
}

void ALiteEnemy::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void ALiteEnemy::Attack() {
    Super::Attack();

    UE_LOG(LogTemp, Warning, TEXT("Enemy is attacking"));
    
    FCollisionShape VisibilitySphere = FCollisionShape::MakeSphere(400.f);
    FVector Start = GetActorLocation(); // TODO: replace with scene component

    FHitResult OutHitResult;
    if(GetWorld()->SweepSingleByChannel(OutHitResult, Start, Start, FQuat::Identity, ECC_GameTraceChannel3, VisibilitySphere)){
        AActor* HitActor = OutHitResult.GetActor();
        if(HitActor){
            UE_LOG(LogTemp, Warning, TEXT("we see %s"), *HitActor->GetActorNameOrLabel());
            UHealthComponent* HC = HitActor->FindComponentByClass<UHealthComponent>();
            if(HC){
                HC->TakeDamage(GetDamageAmount());
            }
        }
    }
}

void ALiteEnemy::HandleTakeDamage() {
    Super::HandleTakeDamage();
}