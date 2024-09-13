#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

UCLASS()
class STORM_API APickupBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* AbilityMesh;
	
public:	
	APickupBase();

protected:
	virtual void BeginPlay() override;

	virtual void AddPickupToPlayer(class APlayerCharacter &Player) {}

	void HandleDestruction();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

};
