
#include "BTTask_SetNewBehaviorToChase.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_SetNewBehaviorToChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        int32 seconds = 0;
        float remaining = 0.0f;
        UGameplayStatics::GetAccurateRealTime(GetWorld(), seconds, remaining);
        aiController->timerStart = seconds + remaining;

        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID(), ASDTAIController::PlayerInteractionBehavior_Chase);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}


