#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class STORM_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

private:

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent* EnemyMesh;

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
