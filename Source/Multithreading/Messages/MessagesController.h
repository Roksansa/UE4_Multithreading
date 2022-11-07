// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MessageEndpoint.h"
#include "CoreMinimal.h"
#include "MessagesController.generated.h"

USTRUCT()
struct FMultithreadingMessageLog
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString TextToLog;

	FMultithreadingMessageLog()
	{
	}

	FMultithreadingMessageLog(const FString& String)
		: TextToLog(String)
	{
	};
};


class MULTITHREADING_API FMultithreadingMessagesController
{
	friend class AMultithreadingGameModeBase;

public:
	void HandleMultithreadingMessageLog(const FMultithreadingMessageLog& MultithreadingMessageLog,
		const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext);

	static void PublishMultithreadingMessageLog(TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint,
		const FString& MessageLog);
	~FMultithreadingMessagesController();

protected:
	void Startup();

private:
	/** Holds the messaging endpoint. */
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;
};
