#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_isLosTimerExpired.generated.h"

/**
 *
 */
UCLASS()
class SOFTDESIGNTRAINING_API UBTService_isLosTimerExpired : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_isLosTimerExpired();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};

