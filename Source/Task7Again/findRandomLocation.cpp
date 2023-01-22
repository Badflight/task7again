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
	//get the pawn and controller
	auto const controller = Cast<AEnemyController>(owner_Comp.GetAIOwner());
	auto const npc = controller->GetPawn();
	//get the current location of the pawn
	FVector const origin = npc->GetActorLocation();
	//sets the nav ssytem
	FNavLocation location;
	UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	//will set the random location based on the search radius and origin
	if (navSys->GetRandomPointInNavigableRadius(origin, searchRadius, location, nullptr))
	{
		//will set the blackboard key for target location.
		controller->get_blackboard()->SetValueAsVector(blackboard_keys::targetLocation, location.Location);
	}
	// will tell the tree when the task is compreted.
	FinishLatentTask(owner_Comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
