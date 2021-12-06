#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_IsPlayerPoweredUp.generated.h"

/**
 *
 */
UCLASS()
class SOFTDESIGNTRAINING_API UBTService_IsPlayerPoweredUp : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_IsPlayerPoweredUp();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};

