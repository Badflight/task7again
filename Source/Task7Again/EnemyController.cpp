// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Task7AgainCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

AEnemyController::AEnemyController(FObjectInitializer const& object_initializer)
{
	//Finds the behavior tree within the project
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/EnnemyBT.EnnemyBT'"));
	if (obj.Succeeded())
	{
		Btree = obj.Object;
	}

	//Sets up the blackboard and behavior component
	behaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this,TEXT("BehaviorComponent"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

	//runs the set up for the perception tree
	setupPerceptionSystem();
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	//runs the behavior tree
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

void AEnemyController::onUpdate(TArray<AActor*> const& updateActors)
{

}

void AEnemyController::onTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast<ATask7AgainCharacter>(actor))
	{
		get_blackboard()->SetValueAsBool(blackboard_keys::canSeePlayer, stimulus.WasSuccessfullySensed());
	}
}

void AEnemyController::setupPerceptionSystem()
{
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (sightConfig) {
		//makes the perception component
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		//sets the range
		sightConfig->SightRadius = 500.0f;
		sightConfig->LoseSightRadius = sightConfig->SightRadius + 50.0f;
		sightConfig->PeripheralVisionAngleDegrees = 90.0f;
		//max age is how long until the ai forgets
		sightConfig->SetMaxAge(5.0f);
		sightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
		//the type of characters the perception can detect
		sightConfig->DetectionByAffiliation.bDetectEnemies = true;
		sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		//
		GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::onTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*sightConfig);
	}
}
