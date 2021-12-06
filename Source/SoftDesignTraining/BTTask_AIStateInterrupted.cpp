
#include "BTTask_AIStateInterrupted.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_AIStateInterrupted::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {

        bool isTargetReach = false;
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

        if (aiController->GetMoveStatus() == EPathFollowingStatus::Idle) {
            isTargetReach = true;
        }
        ASDTAIController::PlayerInteractionBehavior currentBehavior = ASDTAIController::PlayerInteractionBehavior(blackboard->GetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID()));
        if (blackboard->GetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID()) != currentBehavior) {
            isTargetReach = true;
            blackboard->SetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID(), currentBehavior);
        }

        if (isTargetReach == true) {
            aiController->StopMovement();
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}


