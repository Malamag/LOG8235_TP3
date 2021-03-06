// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SDTBaseAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SDTChaseGroupManager.h"

#include "SDTAIController.generated.h"

/**
 *
 */
UCLASS(ClassGroup = AI, config = Game)
class SOFTDESIGNTRAINING_API ASDTAIController : public ASDTBaseAIController
{
    GENERATED_BODY()

public:
    ASDTAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return m_behaviorTreeComponent; }
    UBlackboardComponent* GetBlackBoardComponent() const { return m_blackboardComponent; }

    void                    StartBehaviorTree(APawn* pawn);
    void                    StopBehaviorTree(APawn* pawn);

    enum PlayerInteractionBehavior
    {
        PlayerInteractionBehavior_Collect,
        PlayerInteractionBehavior_Chase,
        PlayerInteractionBehavior_Flee
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
        float m_DetectionCapsuleHalfLength = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
        float m_DetectionCapsuleRadius = 250.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
        float m_DetectionCapsuleForwardStartingOffset = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
        UCurveFloat* JumpCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
        float JumpApexHeight = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
        float JumpSpeed = 1.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
        bool AtJumpSegment = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
        bool InAir = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
        bool Landing = false;
    
protected:

    void GetHightestPriorityDetectionHit(const TArray<FHitResult>& hits, FHitResult& outDetectionHit);
    void UpdatePlayerInteractionBehavior(const FHitResult& detectionHit, float deltaTime);
    PlayerInteractionBehavior GetCurrentPlayerInteractionBehavior(const FHitResult& hit);
    bool HasLoSOnHit(const FHitResult& hit);
    void MoveToRandomCollectible();
    void MoveToPlayer();
    void MoveToBestFleeLocation();
    void PlayerInteractionLoSUpdate();
    void OnPlayerInteractionNoLosDone();
    void OnMoveToTarget();

    virtual void OnPossess(APawn* pawn) override;
    virtual void BeginPlay() override;

public:
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
    void RotateTowards(const FVector& targetLocation);
    void SetActorLocation(const FVector& targetLocation);
    void AIStateInterrupted();
    void JoinChaseGroup();
    void LeaveChaseGroup();
    FVector GetChaseLocation();
    void ResetState();
    void SetBlackboardDefaultState(APawn* pawn);
    void UpdateBehaviorTreeCanExecute(APawn* pawn, bool canExecute);
    void UpdateBehaviorTreeIsAgentAtJumpSegment(APawn* pawn, bool atJumpSegment);
    void UpdateBehaviorTreeIsAgentLanding(APawn* pawn, bool isAgentLanding);
    void UpdateBehaviorTreeIsAgentInTheAir(APawn* pawn, bool isAgentInTheAir);
    uint8 GetTargetPositionBBKeyID() { return m_targetPositionBBKeyID; }
    uint8 GetIsPlayerPowerUpBBKeyID() { return m_isPlayerPowerUpBBKeyID; }
    uint8 GetNewBehaviorBBKeyID() { return m_newBehaviorBBKeyID; }
    uint8 GetAgentBehaviorBBKeyID() { return m_agentBehaviorBBKeyID; }
    uint8 GetLoSTimerStartTimeBBKeyID() { return m_losTimerStartTimeBBKeyID; }
    uint8 GetIsLoSTimerActiveBBKeyID() { return m_isLoSTimerActiveBBKeyID; }
    uint8 GetWasPlayerInLoSBBKeyID() { return m_wasPlayerInLoSBBKeyID; }
    uint8 GetIsAgentInTheAirBBKeyID() { return m_isAgentInTheAirBBKeyID; }
    uint8 GetIsAgentLandingBBKeyID() { return m_isAgentLandingBBKeyID; }
    uint8 GetIsAgentAtJumpSegmentBBKeyID() { return m_isAgentAtJumpSegmentBBKeyID; }
    uint8 GetReachedDestinationBBKeyID() { return m_reachedDestinationBBKeyID; }
    uint8 GetCanExecuteBBKeyID() { return m_canExecuteBBKeyID; }

    float fleeAndCollectTimerStart = 0.0f;
    float detectTimerStart = 0.0f;
    FString fleeAndCollectTimeString = "";
    FString detectTimeString = "";

    virtual void Tick(float deltaTime) override;

private:
    virtual void GoToBestTarget(float deltaTime) override;
    virtual void UpdatePlayerInteraction(float deltaTime) override;
    virtual void ShowNavigationPath() override;

    UPROPERTY(transient)
        UBehaviorTreeComponent* m_behaviorTreeComponent;

    UPROPERTY(transient)
        UBlackboardComponent* m_blackboardComponent;

protected:
    FVector m_JumpTarget;
    FRotator m_ObstacleAvoidanceRotation;
    FTimerHandle m_PlayerInteractionNoLosTimer;
    PlayerInteractionBehavior m_PlayerInteractionBehavior;

    uint8 m_agentBehaviorBBKeyID;
    uint8 m_targetPositionBBKeyID;
    uint8 m_isPlayerPowerUpBBKeyID;
    uint8 m_newBehaviorBBKeyID;
    uint8 m_losTimerStartTimeBBKeyID;
    uint8 m_isLoSTimerActiveBBKeyID;
    uint8 m_wasPlayerInLoSBBKeyID;
    uint8 m_isAgentInTheAirBBKeyID;
    uint8 m_isAgentLandingBBKeyID;
    uint8 m_isAgentAtJumpSegmentBBKeyID;
    uint8 m_reachedDestinationBBKeyID;
    uint8 m_canExecuteBBKeyID;

    ASDTChaseGroupManager* m_chaseGroupManager;
};
