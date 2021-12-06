// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GetPriorityHit.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

EBTNodeResult::Type UBTTask_GetPriorityHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
        APawn* selfPawn = Cast<APawn>(blackboard->GetValue<UBlackboardKeyType_Object>(OwnerComp.GetBlackboardComponent()->GetKeyID("SelfActor")));
        FVector detectionStartLocation = selfPawn->GetActorLocation() + selfPawn->GetActorForwardVector() * aiController->m_DetectionCapsuleForwardStartingOffset;
        FVector detectionEndLocation = detectionStartLocation + selfPawn->GetActorForwardVector() * aiController->m_DetectionCapsuleHalfLength * 2;
  
        TArray<TEnumAsByte<EObjectTypeQuery>> detectionTraceObjectTypes;
        detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));
        detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_COLLECTIBLE));

        TArray<FHitResult> allDetectionHits;
        GetWorld()->SweepMultiByObjectType(allDetectionHits, detectionStartLocation, detectionEndLocation, FQuat::Identity, detectionTraceObjectTypes, FCollisionShape::MakeSphere(aiController->m_DetectionCapsuleRadius));

        FVector impactPoint = FVector::ZeroVector;
        FVector traceStart = FVector::ZeroVector;

        AActor* collisionActor = nullptr;

        ECollisionChannel collisionChannel;

        bool isCollisionOk = false;
        
        for (const FHitResult& hit : allDetectionHits)
        {

            if (UPrimitiveComponent* component = hit.GetComponent())
            {
                
                if (component->GetCollisionObjectType() == COLLISION_PLAYER)
                {
                    blackboard->SetValue<UBlackboardKeyType_Int>(aiController->GetCollisionChannelBBKeyID(), COLLISION_PLAYER);
                    blackboard->SetValue<UBlackboardKeyType_Object>(aiController->GetCollisionActorBBKeyID(), hit.GetActor());
                    blackboard->SetValue<UBlackboardKeyType_Vector>(aiController->GetCollisionImpactPointBBKeyID(), hit.ImpactPoint);
                    blackboard->SetValue<UBlackboardKeyType_Vector>(aiController->GetCollisionImpactTraceStartBBKeyID(), hit.TraceStart);
                    return EBTNodeResult::Succeeded;
                }
                else if (component->GetCollisionObjectType() == COLLISION_COLLECTIBLE)
                {
                    collisionChannel = COLLISION_COLLECTIBLE;
                    isCollisionOk = true;
                    impactPoint = hit.ImpactPoint;
                    traceStart = hit.TraceStart;
                    collisionActor = hit.GetActor();    
                }
                

                
            }
        }

        if (isCollisionOk) {
            blackboard->SetValue<UBlackboardKeyType_Int>(aiController->GetCollisionChannelBBKeyID(), collisionChannel);
            blackboard->SetValue<UBlackboardKeyType_Object>(aiController->GetCollisionActorBBKeyID(), collisionActor);
            blackboard->SetValue<UBlackboardKeyType_Vector>(aiController->GetCollisionImpactPointBBKeyID(), impactPoint);
            blackboard->SetValue<UBlackboardKeyType_Vector>(aiController->GetCollisionImpactTraceStartBBKeyID(), traceStart);
        }

    }

    return EBTNodeResult::Failed;
}




