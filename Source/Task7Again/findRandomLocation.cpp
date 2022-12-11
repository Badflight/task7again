// Fill out your copyright notice in the Description page of Project Settings.


#include "findRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboard_keys.h"

UfindRandomLocation::UfindRandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UfindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* nodeMemory)
{
	auto const cont = Cast<AEnemyController>(owner_Comp.GetAIOwner());
	auto const npc = cont->GetPawn();

	FVector const origin = npc->GetActorLocation();

	FNavLocation location;
	UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	
	if (navSys->GetRandomPointInNavigableRadius(origin, searchRadius, location, nullptr))
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::targetLocation, location.Location);
	}

	FinishLatentTask(owner_Comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
