#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorDamaged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STORM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float Health = 0.f;

public:	

	UHealthComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float DamageValue);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActorDamaged OnActorDamaged;

	void ResetHealth();

	float GetHealthPercent() const;
};
