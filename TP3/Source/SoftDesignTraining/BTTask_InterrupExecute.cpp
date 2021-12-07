
#include "BTTask_InterrupExecute.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "AIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_InterrupExecute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetCanExecuteBBKeyID(), false);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}


