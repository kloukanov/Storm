#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "HealthPickup.generated.h"

UCLASS()
class STORM_API AHealthPickup : public APickupBase
{
	GENERATED_BODY()
	
public:

	AHealthPickup();

protected:

	virtual void BeginPlay() override;

	virtual void AddPickupToPlayer(class APlayerCharacter &Player) override;

public:	

	virtual void Tick(float DeltaTime) override;

};
