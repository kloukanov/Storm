#include "AmmoPickup.h"
#include "../PlayerCharacter.h"

AAmmoPickup::AAmmoPickup(){ }

void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoPickup::AddPickupToPlayer(class APlayerCharacter &Player) {
    UE_LOG(LogTemp, Warning, TEXT("collected ability %s "), *GetActorNameOrLabel());
    Player.AddBulletRoundToGuns();
    HandleDestruction();
}