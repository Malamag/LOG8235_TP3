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
    void ClearChasePoints();
    void UpdateChasePoints();
    void RegisterAIAgent(ASDTBaseAIController* aiAgent);
    void UnregisterAIAgent(ASDTBaseAIController* aiAgent);
    void DrawChasePoints();
    void DisplayGroupMember();
    FVector GetChaseLocation(int groupNumber);

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:

    void AssignChasePointsToAiActors();

    float m_radius = 250;
    ACharacter* m_target;
    TArray<FVector> m_chasePoints;

    TArray<ASDTBaseAIController*> m_registeredAgents;

};
