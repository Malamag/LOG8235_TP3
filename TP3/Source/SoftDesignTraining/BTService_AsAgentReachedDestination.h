#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AsAgentReachedDestination.generated.h"

/**
 *
 */
UCLASS()
class SOFTDESIGNTRAINING_API UBTService_AsAgentReachedDestination : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_AsAgentReachedDestination();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
