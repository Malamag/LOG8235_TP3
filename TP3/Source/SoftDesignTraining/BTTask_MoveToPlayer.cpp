
#include "BTTask_MoveToPlayer.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "AIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

        if (playerCharacter) {
            aiController->StopMovement();
            aiController->MoveToActor(playerCharacter, 0.5f, false, true, true, NULL, false);
            OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsAgentIdleBBKeyID(), false);
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}


