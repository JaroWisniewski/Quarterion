// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "PatrolRoute.h"


TArray<AActor*> UPatrolRoute::GetPatrolPoints() const
{
	return ArrPPoints;
}