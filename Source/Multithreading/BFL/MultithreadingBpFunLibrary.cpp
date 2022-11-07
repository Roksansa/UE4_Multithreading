// Fill out your copyright notice in the Description page of Project Settings.

#include "BFL/MultithreadingBpFunLibrary.h"
#include "Actors/MultithreadingActor.h"
#include "Kismet/GameplayStatics.h"

void UMultithreadingBpFunLibrary::PlayMultithreadingByRunnable(int Count)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GEngine->GameViewport->GetWorld(), AMultithreadingActor::StaticClass(), OutActors);
	for (AActor* Actor : OutActors)
	{
		AMultithreadingActor* CastedActor = StaticCast<AMultithreadingActor*>(Actor);
		CastedActor->PlayMultithreadingByRunnable(Count);
		Count += 10000;
	}
}

void UMultithreadingBpFunLibrary::PlayMultithreadingByTask(int Count)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GEngine->GameViewport->GetWorld(), AMultithreadingActor::StaticClass(), OutActors);
	for (AActor* Actor : OutActors)
	{
		AMultithreadingActor* CastedActor = StaticCast<AMultithreadingActor*>(Actor);
		CastedActor->PlayMultithreadingByAsyncTask(Count);
		Count += 10000;
	}
}
