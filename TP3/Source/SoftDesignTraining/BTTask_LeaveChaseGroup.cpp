
#include "BTTask_LeaveChaseGroup.h"
#include "SDTChaseGroupManager.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"

EBTNodeResult::Type UBTTask_LeaveChaseGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
        APawn* selfPawn = Cast<APawn>(blackboard->GetValue<UBlackboardKeyType_Object>(blackboard->GetKeyID("SelfActor")));


        return EBTNodeResult::Succeeded;


    }

    return EBTNodeResult::Failed;
}


