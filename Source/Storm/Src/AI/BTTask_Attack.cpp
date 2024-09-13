#include "BTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Enemy/EnemyBase.h"


UBTTask_Attack::UBTTask_Attack() {
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) { 
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr){
        return EBTNodeResult::Failed;
    }

    AEnemyBase *Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

    if(Enemy == nullptr) {
        return EBTNodeResult::Failed;
    }

    Enemy->Attack();

    return EBTNodeResult::Succeeded;
}