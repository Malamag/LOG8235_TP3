
#include "BTTask_HasLoSOnHit.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

EBTNodeResult::Type UBTTask_HasLoSOnHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {


            return EBTNodeResult::Succeeded;
        
        
    }

    return EBTNodeResult::Failed;
}


