// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GetBestFleeLocation.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTFleeLocation.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


EBTNodeResult::Type UBTTask_GetBestFleeLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        int32 seconds = 0;
        float remaining = 0.0f;
        UGameplayStatics::GetAccurateRealTime(GetWorld(), seconds, remaining);
        aiController->fleeAndCollectTimerStart = seconds + remaining;

        float bestLocationScore = 0.f;
        ASDTFleeLocation* bestFleeLocation = nullptr;

        ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (playerCharacter) {
            UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
            APawn* selfPawn = Cast<APawn>(blackboard->GetValue<UBlackboardKeyType_Object>(blackboard->GetKeyID("SelfActor")));
            FVector selfLocation = selfPawn->GetActorLocation();

            for (TActorIterator<ASDTFleeLocation> actorIterator(GetWorld(), ASDTFleeLocation::StaticClass()); actorIterator; ++actorIterator)
            {
                ASDTFleeLocation* fleeLocation = Cast<ASDTFleeLocation>(*actorIterator);
                if (fleeLocation)
                {
                    float distToFleeLocation = FVector::Dist(fleeLocation->GetActorLocation(), playerCharacter->GetActorLocation());

                    FVector selfToPlayer = playerCharacter->GetActorLocation() - selfLocation;
                    selfToPlayer.Normalize();

                    FVector selfToFleeLocation = fleeLocation->GetActorLocation() - selfLocation;
                    selfToFleeLocation.Normalize();

                    float fleeLocationToPlayerAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(selfToPlayer, selfToFleeLocation)));
                    float locationScore = distToFleeLocation + fleeLocationToPlayerAngle * 100.f;

                    if (locationScore > bestLocationScore)
                    {
                        bestLocationScore = locationScore;
                        bestFleeLocation = fleeLocation;
                        blackboard->SetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPositionBBKeyID(), bestFleeLocation->GetActorLocation());
                    }
                }
            }

            if (bestFleeLocation) {
                return EBTNodeResult::Succeeded;
            }
        }

    }
    return EBTNodeResult::Failed;
}




