// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Task7AgainCharacter.h"

AEnemyController::AEnemyController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/EnnemyBT.EnnemyBT'"));
	if (obj.Succeeded())
	{
		Btree = obj.Object;
	}
	behaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this,TEXT("BehaviorComponent"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(Btree);
	behaviorTreeComponent->StartTree(*Btree);
}

void AEnemyController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*Btree->BlackboardAsset);
	}
}

UBlackboardComponent* AEnemyController::get_blackboard() const
{
	return blackboard;
}
