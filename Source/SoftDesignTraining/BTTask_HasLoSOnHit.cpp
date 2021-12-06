
#include "BTTask_HasLoSOnHit.h"
#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

EBTNodeResult::Type UBTTask_HasLoSOnHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {

        APawn* selfPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OwnerComp.GetBlackboardComponent()->GetKeyID("SelfActor")));

        TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
        TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

        FVector impactPoint = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->GetCollisionImpactPointBBKeyID());
        FVector traceStart = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->GetCollisionImpactTraceStartBBKeyID());

        FVector hitDirection = impactPoint - traceStart;
        hitDirection.Normalize();

        FHitResult losHit;
        FCollisionQueryParams queryParams = FCollisionQueryParams();

        AActor* collisionActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(aiController->GetCollisionActorBBKeyID()));
        queryParams.AddIgnoredActor(collisionActor);

        GetWorld()->LineTraceSingleByObjectType(losHit, traceStart, impactPoint + hitDirection, TraceObjectTypes, queryParams);

        if (losHit.GetActor() == nullptr) {
            return EBTNodeResult::Succeeded;
        }
        
    }

    return EBTNodeResult::Failed;
}


