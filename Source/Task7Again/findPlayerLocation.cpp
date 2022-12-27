// Fill out your copyright notice in the Description page of Project Settings.


#include "findPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFrameWork/Character.h"
#include "blackboard_keys.h"

UfindPlayerLocation::UfindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UfindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	auto const cont = Cast<AEnemyController>(owner_comp.GetAIOwner());

	FVector const playerLocation = player->GetActorLocation();
	if (search_random)
	{
		FNavLocation loc;

		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(playerLocation, search_radius, loc, nullptr))
		{
			cont->get_blackboard()->SetValueAsVector(blackboard_keys::targetLocation, loc.Location);
		}
	}
	else
	{
		cont->get_blackboard()->SetValueAsVector(blackboard_keys::targetLocation, playerLocation);
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
