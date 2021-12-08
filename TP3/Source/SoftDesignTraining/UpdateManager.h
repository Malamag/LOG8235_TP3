#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "SoftDesignTrainingCharacter.h"
#include "UpdateManager.generated.h"

const double BUDGET = 0.000005; // max CPU usage is 5 ms

UCLASS()
class SOFTDESIGNTRAINING_API AUpdateManager : public AActor
{
	GENERATED_BODY()

public:
	AUpdateManager();

protected:
	virtual void BeginPlay() override;
private:
	TArray < ASoftDesignTrainingCharacter* > m_AICharacters;
	int m_lastUpdatedAgentIndex = -1;
	void GetAllCharacters();

public:
	virtual void Tick(float DeltaTime) override;

};
