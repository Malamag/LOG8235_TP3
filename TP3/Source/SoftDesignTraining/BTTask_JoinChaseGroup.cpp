

#include "BTTask_JoinChaseGroup.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SDTChaseGroupManager.h"
#include "SoftDesignTrainingCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"

EBTNodeResult::Type UBTTask_JoinChaseGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
        APawn* selfPawn = Cast<APawn>(blackboard->GetValue<UBlackboardKeyType_Object>(blackboard->GetKeyID("SelfActor")));

        //DrawDebugString(GetWorld(), FVector(0.f, 0.f, 100.f), "Try Joinning Group", selfPawn, FColor::Red, 5.f, false);
        aiController->JoinChaseGroup();

        return EBTNodeResult::Succeeded;


    }

    return EBTNodeResult::Failed;
}


