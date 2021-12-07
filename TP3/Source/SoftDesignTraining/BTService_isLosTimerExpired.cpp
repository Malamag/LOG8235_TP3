
#include "BTService_isLosTimerExpired.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"

UBTService_isLosTimerExpired::UBTService_isLosTimerExpired()
{
    bCreateNodeInstance = true;
}

void UBTService_isLosTimerExpired::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
        if (blackboard->GetValue<UBlackboardKeyType_Bool>(aiController->GetIsLoSTimerActiveBBKeyID())) {

            float timerStartTime = blackboard->GetValue<UBlackboardKeyType_Float>(aiController->GetLoSTimerStartTimeBBKeyID());
            int currentSecond;
            float currentPartialSecond;

            UGameplayStatics::GetAccurateRealTime(GetWorld(), currentSecond, currentPartialSecond);
            float currentTime = currentSecond + currentPartialSecond;

            if (currentTime - timerStartTime >= 3.0f) {
                blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsLoSTimerActiveBBKeyID(), false);
                blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetWasPlayerInLoSBBKeyID(), false);
            }
        }
        int32 seconds = 0;
        float remaining = 0.0f;
        UGameplayStatics::GetAccurateRealTime(GetWorld(), seconds, remaining);
        float endTime = seconds + remaining;
        aiController->detectTimeString = FString("Detect\nExecTime:") + FString::SanitizeFloat(endTime - aiController->detectTimerStart);
    }

}


