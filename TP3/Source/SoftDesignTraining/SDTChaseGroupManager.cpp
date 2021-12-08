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

	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ASDTChaseGroupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DisplayGroupMembers();
}

void ASDTChaseGroupManager::SetChasePoints()
{
	if (m_registeredAgents.Num() == 1) {
		m_chasePoints.Add(player->GetActorLocation());
		m_registeredAgents[0]->m_groupNumber = 0;
	}
	else {
		int32 numAgents = m_registeredAgents.Num();
		for (int i = 0; i < m_registeredAgents.Num(); i++) {
			float curAngle = (2*PI*i / numAgents); //angle sur le cercle
			FVector chasePoint = FVector(circle_radius * cos(curAngle), circle_radius * sin(curAngle), 0);
			m_chasePoints.Add(chasePoint);
			m_registeredAgents[i]->m_groupNumber = i;
		}
	}
}

void ASDTChaseGroupManager::AddAgent(ASDTBaseAIController* aiAgent)
{
	if (!m_registeredAgents.Contains(aiAgent)) {
		m_registeredAgents.Add(aiAgent);		
		m_chasePoints.Empty();
		SetChasePoints();
	}
}

void ASDTChaseGroupManager::RemoveAgent(ASDTBaseAIController* aiAgent)
{
	if (m_registeredAgents.Contains(aiAgent)) {
		m_registeredAgents.Remove(aiAgent);
		m_chasePoints.Empty();
		SetChasePoints();
	}
	
}

void ASDTChaseGroupManager::MoveToChasePoints()
{
	for (int i = 0; i < m_registeredAgents.Num(); i++) {
		m_registeredAgents[i]->MoveToLocation(player->GetActorLocation() + m_chasePoints[i], 0.5f);
	}
}

FVector ASDTChaseGroupManager::GetChaseLocation(int groupNumber) {

	return player->GetActorLocation() + m_chasePoints[groupNumber];
}

void ASDTChaseGroupManager::DisplayGroupMembers()
{
	for (int i = 0; i < m_registeredAgents.Num(); i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::FString(m_registeredAgents[i]->GetName()));
	}
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::FString("Membre du groupe de poursuite :"));
}
