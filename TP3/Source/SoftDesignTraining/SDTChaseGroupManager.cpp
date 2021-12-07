// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTChaseGroupManager.h"
#include "SDTAIController.h"
#include "SoftDesignTraining.h"
#include "DrawDebugHelpers.h"
#include <cmath>
#include "Engine.h"

ASDTChaseGroupManager::ASDTChaseGroupManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASDTChaseGroupManager::BeginPlay()
{
	Super::BeginPlay();

	m_target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ASDTChaseGroupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawChasePoints();
	DisplayGroupMember();
	AssignChasePointsToAiActors();
}

void ASDTChaseGroupManager::ClearChasePoints()
{
	m_chasePoints.Empty();
}

void ASDTChaseGroupManager::UpdateChasePoints()
{
	FVector chasePoint = m_target->GetActorLocation();
	if (m_registeredAgents.Num() == 1) {
		m_chasePoints.Add(FVector(0, 0, 0));
	}
	else {
		for (int i = 0; i < m_registeredAgents.Num(); i++) {
			float currentAngle = (i * 2 * PI) / m_registeredAgents.Num();
			float x = m_radius * cos(currentAngle);
			float y = m_radius * sin(currentAngle);
			FVector offset = FVector(x, y, 0);

			//chasePoint += offset;
			m_chasePoints.Add(offset);
		}
	}
}

void ASDTChaseGroupManager::RegisterAIAgent(ASDTBaseAIController* aiAgent)
{
	if (!m_registeredAgents.Contains(aiAgent)) {
		m_registeredAgents.Add(aiAgent);		
		ClearChasePoints();
		UpdateChasePoints();
		//AssignChasePointsToAiActors();
	}
}

void ASDTChaseGroupManager::UnregisterAIAgent(ASDTBaseAIController* aiAgent)
{
	if (m_registeredAgents.Contains(aiAgent)) {
		m_registeredAgents.Remove(aiAgent);
		ClearChasePoints();
		UpdateChasePoints();
		//AssignChasePointsToAiActors();
	}
	
}

void ASDTChaseGroupManager::AssignChasePointsToAiActors()
{
	for (int i = 0; i < m_registeredAgents.Num(); i++) {
		//m_registeredAgents[i]->StopMovement();
		m_registeredAgents[i]->MoveToLocation(m_target->GetActorLocation() + m_chasePoints[i], 0.5f);
		//m_registeredAgents[i]->SetChasePoint(m_chasePoints[i]);
	}
}

void ASDTChaseGroupManager::DrawChasePoints()
{
	for (int i = 0; i < m_chasePoints.Num(); i++)
	{
		DrawDebugSphere(GetWorld(), m_target->GetActorLocation() + m_chasePoints[i], 15.0f, 100, FColor::Red);
	}
}

void ASDTChaseGroupManager::DisplayGroupMember()
{
	for (int i = 0; i < m_registeredAgents.Num(); i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::FString(m_registeredAgents[i]->GetName()));
	}
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::FString("Membre du groupe de poursuite :"));
}

/*TargetLKPInfo AiAgentGroupManager::GetLKPFromGroup(const FString& targetLabel, bool& targetfound)
{
    int agentCount = m_registeredAgents.Num();
    TargetLKPInfo outLKPInfo = TargetLKPInfo();
    targetfound = false;

    for (int i = 0; i < agentCount; ++i)
    {
        AAIBase* aiAgent = m_registeredAgents[i];
        if (aiAgent)
        {
            const TargetLKPInfo& targetLKPInfo = aiAgent->GetCurrentTargetLKPInfo();
            if (targetLKPInfo.GetTargetLabel() == targetLabel)
            {
                if (targetLKPInfo.GetLastUpdatedTimeStamp() > outLKPInfo.GetLastUpdatedTimeStamp())
                {
                    targetfound = targetLKPInfo.GetLKPState() != TargetLKPInfo::ELKPState::LKPState_Invalid;
                    outLKPInfo = targetLKPInfo;
                }
            }
        }
    }

    return outLKPInfo;
}*/