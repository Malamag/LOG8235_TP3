// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GetClosestCollectible.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTCollectible.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_GetClosestCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
        APawn* selfPawn = Cast<APawn>(blackboard->GetValue<UBlackboardKeyType_Object>(blackboard->GetKeyID("SelfActor")));
        float closestSqrCollectibleDistance = 18446744073709551610.f;
        ASDTCollectible* closestCollectible = nullptr;

        TArray<AActor*> foundCollectibles;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTCollectible::StaticClass(), foundCollectibles);

        while (foundCollectibles.Num() != 0)
        {
            int index = FMath::RandRange(0, foundCollectibles.Num() - 1);

            ASDTCollectible* collectibleActor = Cast<ASDTCollectible>(foundCollectibles[index]);
            if (!collectibleActor) {
                return EBTNodeResult::Failed;
            }

            if (!collectibleActor->IsOnCooldown())
            {
                
                blackboard->SetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPositionBBKeyID(), collectibleActor->GetActorLocation());
                return EBTNodeResult::Succeeded;
            }
            else
            {
                foundCollectibles.RemoveAt(index);
            }
                   
        }

    }
    return EBTNodeResult::Failed;
}




