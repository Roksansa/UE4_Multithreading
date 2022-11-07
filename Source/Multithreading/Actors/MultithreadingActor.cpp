// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MultithreadingActor.h"
#include "MessageEndpointBuilder.h"
#include "AsyncTasks/SimpleAsyncTask.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SimpleRunnable/SimpleRunnable.h"

AMultithreadingActor::AMultithreadingActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMultithreadingActor::PlayMultithreadingByRunnable(int Count)
{
	if (FPlatformProcess::SupportsMultithreading() && RunnableMessageEndpoint.IsValid())
	{
#if WITH_EDITOR
		FString NameRunnable = GetActorLabel();
#else
		FString NameRunnable = GetName();
#endif
		NameRunnable.Appendf(TEXT("____%d"), CurrentRun++);
		FSimpleRunnable* MyRunnable = new FSimpleRunnable(NameRunnable, Count, RunnableMessageEndpoint->AsWeak());
		SimpleRunnables.Add(MyRunnable);
	}
}

void AMultithreadingActor::PlayMultithreadingByAsyncTask(int Count)
{
	if (AsyncTaskMessageEndpoint.IsValid())
	{
#if WITH_EDITOR
		FString NameRunnable = GetActorLabel();
#else
		FString NameRunnable = GetName();
#endif
		NameRunnable.Appendf(TEXT("____%d"), CurrentRun++);
		(new FAutoDeleteAsyncTask<FSimpleAsyncTask>(NameRunnable, Count, AsyncTaskMessageEndpoint->AsWeak()))->StartBackgroundTask();
	}
}


void AMultithreadingActor::BeginPlay()
{
	Super::BeginPlay();
	SimpleRunnables.Empty();
	CurrentRun = 0;
	RunnableMessageEndpoint = FMessageEndpoint::Builder("FSimpleRunnable");
	AsyncTaskMessageEndpoint = FMessageEndpoint::Builder("FSimpleAsyncTask");
}

void AMultithreadingActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto& SRun : SimpleRunnables)
	{
		SRun->KillThread();
		delete SRun;
		SRun = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}
