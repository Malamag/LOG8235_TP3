
#include "BTService_IsPlayerPoweredUp.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTService_IsPlayerPoweredUp::UBTService_IsPlayerPoweredUp()
{
    bCreateNodeInstance = true;
}

void UBTService_IsPlayerPoweredUp::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsPlayerPowerUpBBKeyID(), SDTUtils::IsPlayerPoweredUp(GetWorld()));
    }
}


