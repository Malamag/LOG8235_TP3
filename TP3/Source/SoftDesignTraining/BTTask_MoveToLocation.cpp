
#include "BTTask_MoveToLocation.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        aiController->StopMovement();
        FVector targetLocation = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPositionBBKeyID());
        aiController->MoveToLocation(targetLocation, 0.5f, false, true, false, NULL, false);
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsAgentIdleBBKeyID(), false);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}


