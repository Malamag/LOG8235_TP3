#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateLoS.generated.h"

/**
 *
 */
UCLASS()
class SOFTDESIGNTRAINING_API UBTService_UpdateLoS : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateLoS();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};

