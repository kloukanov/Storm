#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(float DamageValue) {
	Health -= DamageValue;
	OnActorDamaged.Broadcast();

	if(Health <= 0.f) {
		ASGameMode* SGameMode = Cast<ASGameMode>(UGameplayStatics::GetGameMode(this));
		SGameMode->ActorDied(GetOwner());
	}

	UE_LOG(LogTemp, Warning, TEXT("health = %f"), Health);
}

void UHealthComponent::ResetHealth() {
	Health = MaxHealth;
}

float UHealthComponent::GetHealthPercent() const {
	return Health / MaxHealth;
}