#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay() {
    Super::BeginPlay();

    // APawn* AIPawn = GetPawn();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AIBehavior){
        RunBehaviorTree(AIBehavior);
        if(PlayerPawn){
            GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
            // TargetLocation = GetPawn()->GetActorLocation();
            // GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
            // GetBlackboardComponent()->SetValueAsBool(TEXT("IsAIStuck"), IsAIStuck);
        }
    }
}