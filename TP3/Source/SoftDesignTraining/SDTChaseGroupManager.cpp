// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTChaseGroupManager.h"
#include "SoftDesignTraining.h"

SDTChaseGroupManager* SDTChaseGroupManager::m_Instance;

SDTChaseGroupManager::SDTChaseGroupManager()
{
}

SDTChaseGroupManager* SDTChaseGroupManager::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = new SDTChaseGroupManager();
    }

    return m_Instance;
}

void SDTChaseGroupManager::Destroy()
{
    delete m_Instance;
    m_Instance = nullptr;
}

void SDTChaseGroupManager::RegisterAIAgent(ASDTAIController* aiAgent)
{
    m_registeredAgents.Add(aiAgent);
}

void SDTChaseGroupManager::UnregisterAIAgent(ASDTAIController* aiAgent)
{
    m_registeredAgents.Remove(aiAgent);
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