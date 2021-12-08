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

// Sets the chase points in such a way that they're equidistant along an arc
void ASDTChaseGroupManager::SetGroupChasePoints()
{
	if (m_registeredAgents.Num() == 1) { //If only one agent in the group, simply go to player
		m_chasePoints.Add(player->GetActorLocation());
		m_registeredAgents[0]->m_groupNumber = 0;
	}
	else {
		int32 numAgents = m_registeredAgents.Num();
		for (int i = 0; i < m_registeredAgents.Num(); i++) {
			float curAngle = (2*PI*i / numAgents); //angle on the circle
			if (i % 2 == 0) {
				curAngle = int(180 + curAngle) % 360; //Distribute every other agent evenly along the circle
			}
			FVector chasePoint = FVector(circle_radius * cos(curAngle), circle_radius * sin(curAngle), 0);
			m_chasePoints.Add(chasePoint);
			m_registeredAgents[i]->m_groupNumber = i;
		}
	}
}

// Add agent to the group and reset group chase points
void ASDTChaseGroupManager::AddAgent(ASDTBaseAIController* aiAgent)
{
	if (!m_registeredAgents.Contains(aiAgent)) {
		m_registeredAgents.Add(aiAgent);		
		m_chasePoints.Empty();
		SetGroupChasePoints();
	}
}

// Remove agent from the group and reset group chase points
void ASDTChaseGroupManager::RemoveAgent(ASDTBaseAIController* aiAgent)
{
	if (m_registeredAgents.Contains(aiAgent)) {
		m_registeredAgents.Remove(aiAgent);
		m_chasePoints.Empty();
		SetGroupChasePoints();
	}
	
}

//Get a specific group members chase location
FVector ASDTChaseGroupManager::GetChaseLocation(int groupNumber) {

	return player->GetActorLocation() + m_chasePoints[groupNumber];
}

//Display the list of all members of the group
void ASDTChaseGroupManager::DisplayGroupMembers()
{
	for (int i = 0; i < m_registeredAgents.Num(); i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::FString(m_registeredAgents[i]->GetName()));
	}
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::FString("Membre du groupe de poursuite :"));
}
