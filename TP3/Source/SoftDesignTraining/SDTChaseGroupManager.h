#pragma once
//#include "TargetLKPInfo.h"
#include "SDTAIController.h"
#include "CoreMinimal.h"

/**
 *
 */
class SOFTDESIGNTRAINING_API SDTChaseGroupManager
{
public:
    static SDTChaseGroupManager* GetInstance();
    static void Destroy();

    void RegisterAIAgent(ASDTAIController* aiAgent);
    void UnregisterAIAgent(ASDTAIController* aiAgent);

    //TargetLKPInfo GetLKPFromGroup(const FString& targetLabel, bool& targetFound);

private:

    //SINGLETON
    SDTChaseGroupManager();
    static SDTChaseGroupManager* m_Instance;

    TArray<ASDTAIController*> m_registeredAgents;

};
