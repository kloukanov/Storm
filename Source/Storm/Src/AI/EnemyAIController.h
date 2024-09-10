#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class STORM_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected: 

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere, Category = AI)
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = AI)
	bool IsAIStuck = false;

};
