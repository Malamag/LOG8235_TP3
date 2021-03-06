
#include "BTTask_SetNewBehaviorToFlee.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_SetNewBehaviorToFlee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        APawn* selfPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OwnerComp.GetBlackboardComponent()->GetKeyID("SelfActor")));
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID(), ASDTAIController::PlayerInteractionBehavior_Flee);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}


