// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MessageEndpoint.h"
#include "MultithreadingActor.generated.h"

UCLASS()
class MULTITHREADING_API AMultithreadingActor : public AActor
{
	GENERATED_BODY()

public:
	AMultithreadingActor();
	void PlayMultithreadingByRunnable(int Count);
	void PlayMultithreadingByAsyncTask(int Count);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TArray<class FSimpleRunnable*> SimpleRunnables;
	int CurrentRun;

	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> RunnableMessageEndpoint;
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> AsyncTaskMessageEndpoint;
};
