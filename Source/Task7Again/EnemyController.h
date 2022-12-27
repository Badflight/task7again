// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TASK7AGAIN_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;
	class UBlackboardComponent* get_blackboard() const;
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behaviorTreeComponent;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* Btree;

	class UBlackboardComponent* blackboard;

	class UAISenseConfig_Sight* sightConfig;

	UFUNCTION()
		void onUpdate(TArray<AActor*> const& updateActors);
	UFUNCTION()
		void onTargetDetected(AActor*actor, FAIStimulus const stimulus);
	void setupPerceptionSystem();
};
