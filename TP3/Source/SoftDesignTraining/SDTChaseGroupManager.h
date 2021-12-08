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
    void SetGroupChasePoints();
    void AddAgent(ASDTBaseAIController* aiAgent);
    void RemoveAgent(ASDTBaseAIController* aiAgent);
    void DisplayGroupMembers();
    FVector GetChaseLocation(int groupNumber);
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    TArray<ASDTBaseAIController*> m_registeredAgents;

    ACharacter* player;

    float circle_radius = 200;
    TArray<FVector> m_chasePoints;
};
