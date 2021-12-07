
#include "BTTask_MoveToLocation.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
        //aiController->StopMovement();
        FVector targetLocation = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPositionBBKeyID());
        aiController->MoveToLocation(targetLocation, 0.5f, false, true, false, NULL, false);

        int aiState = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID());

        switch (aiState)
        {
        case ASDTAIController::PlayerInteractionBehavior_Collect:
            aiController->fleeAndCollectTimeString = "Collect\nExecTime:";
            break;
        case ASDTAIController::PlayerInteractionBehavior_Flee:
            aiController->fleeAndCollectTimeString = "Flee\nExecTime:";
            break;
        }

        int32 seconds = 0;
        float remaining = 0.0f;
        UGameplayStatics::GetAccurateRealTime(GetWorld(), seconds, remaining);
        float endTime = seconds + remaining;
        aiController->fleeAndCollectTimeString += FString::SanitizeFloat(endTime - aiController->fleeAndCollectTimerStart);

        blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedDestinationBBKeyID(), false);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}


