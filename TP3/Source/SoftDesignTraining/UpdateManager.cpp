
#include "UpdateManager.h"
#include "Kismet/GameplayStatics.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

AUpdateManager::AUpdateManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AUpdateManager::BeginPlay()
{
	Super::BeginPlay();
	GetAllCharacters();
}

void AUpdateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	double timePassed = 0;
	while (timePassed < BUDGET)
	{
		double start = FPlatformTime::Seconds();
		m_lastUpdatedAgentIndex = (m_lastUpdatedAgentIndex + 1) % m_AICharacters.Num();
		if (ASDTAIController* agentController = Cast<ASDTAIController>(m_AICharacters[m_lastUpdatedAgentIndex]->GetController()))
		{
			agentController->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Bool>(agentController->GetCanExecuteBBKeyID(), true);
		}
		timePassed += (FPlatformTime::Seconds() - start);

	}
}

void AUpdateManager::GetAllCharacters()
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoftDesignTrainingCharacter::StaticClass(), foundActors);
	for (int i = 0; i < foundActors.Num(); i++)
	{
		if (ASoftDesignTrainingCharacter* agentCharacter = Cast<ASoftDesignTrainingCharacter>(foundActors[i]))
			m_AICharacters.Push(agentCharacter);
	}
}