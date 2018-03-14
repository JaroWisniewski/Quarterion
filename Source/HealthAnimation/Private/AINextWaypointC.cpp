// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "AINextWaypointC.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAINextWaypointC::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//Get Patrol Points
	auto Character = OwnerComp.GetAIOwner()->GetPawn();

	auto PatrolRoute = Character->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) 
	{
		return EBTNodeResult::Failed;
	}

	auto PPoints = PatrolRoute->GetPatrolPoints();
	if (PPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Points Selected for character %s"), *(Character->GetName()));
		return EBTNodeResult::Failed;
	}

	//Get Next Waypoint


	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	BlackboardComp->SetValueAsObject(WaypointObject.SelectedKeyName, PPoints[Index]);

	auto Index2 = (Index+1) % PPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index2);

	return EBTNodeResult::Succeeded;
}

