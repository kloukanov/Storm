#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "AmmoPickup.generated.h"

UCLASS()
class STORM_API AAmmoPickup : public APickupBase
{
	GENERATED_BODY()
	
public:

	AAmmoPickup();

protected:

	virtual void BeginPlay() override;

	virtual void AddPickupToPlayer(class APlayerCharacter &Player) override;

public:	

	virtual void Tick(float DeltaTime) override;

};

