
#include "BTTask_SetNewBehaviorToCollect.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_SetNewBehaviorToCollect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {

        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID(), ASDTAIController::PlayerInteractionBehavior_Collect);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}


