// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "AINextWaypointC.h"

EBTNodeResult::Type UAINextWaypointC::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
//	auto Index = BlackboardComp
	UE_LOG(LogTemp, Warning, TEXT("We are in"));
	return EBTNodeResult::Succeeded;
}

