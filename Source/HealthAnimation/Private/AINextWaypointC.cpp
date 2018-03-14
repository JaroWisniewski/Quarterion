// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "AINextWaypointC.h"
#include "AIController.h"
#include "PatrollingCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAINextWaypointC::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//Get Patrol Points
	auto AIcontroller = OwnerComp.GetAIOwner();

	auto Character = AIcontroller->GetPawn();

	auto PatrollingGuard = Cast<APatrollingCharacter>(Character);

	auto PPoints = PatrollingGuard->ArrPPoints;

	//Get Next Waypoint


	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	BlackboardComp->SetValueAsObject(WaypointObject.SelectedKeyName, PPoints[Index]);

	auto Index2 = (Index+1) % PPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index2);

	return EBTNodeResult::Succeeded;
}

