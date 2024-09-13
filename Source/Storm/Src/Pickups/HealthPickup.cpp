#include "HealthPickup.h"
#include "../HealthComponent.h"
#include "../PlayerCharacter.h"


AHealthPickup::AHealthPickup(){ }

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealthPickup::AddPickupToPlayer(class APlayerCharacter &Player) {
    UE_LOG(LogTemp, Warning, TEXT("collected ability %s "), *GetActorNameOrLabel());
    UHealthComponent* HC = Player.FindComponentByClass<UHealthComponent>();
    if(HC){
        HC->ResetHealth();
    }
    HandleDestruction();
}