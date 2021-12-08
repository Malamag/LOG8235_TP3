#pragma once
//#include "TargetLKPInfo.h"
#include "SDTBaseAIController.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDTChaseGroupManager.generated.h"

/**
 *
 */
UCLASS()
class SOFTDESIGNTRAINING_API ASDTChaseGroupManager : public AActor
{
    GENERATED_BODY()

public:
    ASDTChaseGroupManager();
    void SetChasePoints();
    void AddAgent(ASDTBaseAIController* aiAgent);
    void RemoveAgent(ASDTBaseAIController* aiAgent);
    void MoveToChasePoints();
    void DisplayGroupMembers();
    FVector GetChaseLocation(int groupNumber);

    TArray<ASDTBaseAIController*> m_registeredAgents;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:

    ACharacter* player;

    float circle_radius = 200;
    TArray<FVector> m_chasePoints;
};
