// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "findRandomLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TASK7AGAIN_API UfindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UfindRandomLocation(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* nodeMemory);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float searchRadius = 1500.0f;
	
};
