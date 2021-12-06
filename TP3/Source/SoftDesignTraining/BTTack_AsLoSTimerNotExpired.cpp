
#include "BTTask_AsLoSTimerNotExpired.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

EBTNodeResult::Type UBTTask_AsLoSTimerNotExpired::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {

        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
        float timerStartTime = blackboard->GetValue<UBlackboardKeyType_Float>(aiController->GetLoSTimerStartTimeBBKeyID());
        int currentSecond;
        float currentPartialSecond;

        UGameplayStatics::GetAccurateRealTime(GetWorld(), currentSecond, currentPartialSecond);
        float currentTime = currentSecond + currentPartialSecond;

        if (currentTime - timerStartTime < 3.0f) {
            return EBTNodeResult::Succeeded;
        } 
        else {
            blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsLoSTimerActiveBBKeyID(), false);
            blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetWasPlayerInLoSBBKeyID(), false);
            blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsAgentIdleBBKeyID(), true);
            return EBTNodeResult::Failed;
        }
         
        

    }

    return EBTNodeResult::Failed;
}


