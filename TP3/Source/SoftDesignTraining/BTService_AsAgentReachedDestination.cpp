
#include "BTService_AsAgentReachedDestination.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"

UBTService_AsAgentReachedDestination::UBTService_AsAgentReachedDestination()
{
    bCreateNodeInstance = true;
}

void UBTService_AsAgentReachedDestination::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

        if (aiController->GetMoveStatus() == EPathFollowingStatus::Idle) {
            blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedDestinationBBKeyID(), true);
            return;
        }

        if (blackboard->GetValue<UBlackboardKeyType_Int>(aiController->GetAgentBehaviorBBKeyID()) != blackboard->GetValue<UBlackboardKeyType_Int>(aiController->GetNewBehaviorBBKeyID())) {
            blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedDestinationBBKeyID(), true);
            return;
        }

        FPathFollowingResult result;
        aiController->OnMoveCompleted(aiController->GetCurrentMoveRequestID(), result);
        if (result.IsSuccess()) {
            blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedDestinationBBKeyID(), true);
        }
        else {
            blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedDestinationBBKeyID(), false);
        }
    }
}


