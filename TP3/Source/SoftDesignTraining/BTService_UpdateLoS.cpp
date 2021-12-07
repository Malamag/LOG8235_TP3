
#include "BTService_UpdateLoS.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTService_UpdateLoS::UBTService_UpdateLoS()
{
    bCreateNodeInstance = true;
}

void UBTService_UpdateLoS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (playerCharacter) {

            UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
            APawn* selfPawn = Cast<APawn>(blackboard->GetValue<UBlackboardKeyType_Object>(blackboard->GetKeyID("SelfActor")));

            TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
            TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
            TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));

            FHitResult losHit;
            GetWorld()->LineTraceSingleByObjectType(losHit, selfPawn->GetActorLocation(), playerCharacter->GetActorLocation(), TraceObjectTypes);

            bool hasLosOnPlayer = false;

            if (losHit.GetComponent())
            {
                if (losHit.GetComponent()->GetCollisionObjectType() == COLLISION_PLAYER)
                {
                    hasLosOnPlayer = true;
                }
            }

            bool isLoSTimerActive = blackboard->GetValue<UBlackboardKeyType_Bool>(aiController->GetIsLoSTimerActiveBBKeyID());
            if (hasLosOnPlayer)
            {
                blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetWasPlayerInLoSBBKeyID(), true);
                if (isLoSTimerActive)
                {
                    blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsLoSTimerActiveBBKeyID(), false);

                    DrawDebugString(GetWorld(), FVector(0.f, 0.f, 10.f), "Got LoS", selfPawn, FColor::Red, 5.f, false);
                }
            }
            else
            {
                if (!isLoSTimerActive)
                {
                    blackboard->SetValue<UBlackboardKeyType_Bool>(aiController->GetIsLoSTimerActiveBBKeyID(), true);
                    int currentSecond;
                    float currentPartialSecond;
                    UGameplayStatics::GetAccurateRealTime(GetWorld(), currentSecond, currentPartialSecond);
                    float currentTime = currentSecond + currentPartialSecond;

                    blackboard->SetValue<UBlackboardKeyType_Float>(aiController->GetLoSTimerStartTimeBBKeyID(), currentTime);
                    DrawDebugString(GetWorld(), FVector(0.f, 0.f, 10.f), "Lost LoS", selfPawn, FColor::Red, 5.f, false);
                }

            }


        }
    }
}


