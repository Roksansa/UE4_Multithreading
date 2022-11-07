// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultithreadingBpFunLibrary.generated.h"

UCLASS()
class MULTITHREADING_API UMultithreadingBpFunLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Create new threads
	 */
	UFUNCTION(BlueprintCallable, Category = Thread)
	static void PlayMultithreadingByRunnable(int Count);

	/**
	 * Work in background threads from pools
	 */
	UFUNCTION(BlueprintCallable, Category = Thread)
	static void PlayMultithreadingByTask(int Count);
};
