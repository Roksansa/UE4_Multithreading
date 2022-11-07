// Fill out your copyright notice in the Description page of Project Settings.


#include "Messages/MessagesController.h"

#include "MessageEndpoint.h"
#include "MessageEndpointBuilder.h"

DEFINE_LOG_CATEGORY_STATIC(LogMultithreadingMessageLog, All, All);

void FMultithreadingMessagesController::Startup()
{
	MessageEndpoint = FMessageEndpoint::Builder("FMultithreadingMessageController")
	                  .ReceivingOnThread(ENamedThreads::GameThread)
	                  .Handling<FMultithreadingMessageLog>(this, &FMultithreadingMessagesController::HandleMultithreadingMessageLog);

	if (MessageEndpoint.IsValid())
	{
		MessageEndpoint->Subscribe<FMultithreadingMessageLog>();
	}
}

FMultithreadingMessagesController::~FMultithreadingMessagesController()
{
	FMessageEndpoint::SafeRelease(MessageEndpoint);
}

void FMultithreadingMessagesController::HandleMultithreadingMessageLog(const FMultithreadingMessageLog& MultithreadingMessageLog,
	const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& MessageContext)
{
	UE_LOG(LogMultithreadingMessageLog, Log, TEXT("%s"), *MultithreadingMessageLog.TextToLog);
}


void FMultithreadingMessagesController::PublishMultithreadingMessageLog(TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint,
	const FString& MessageLog)
{
	if (MessageEndpoint.IsValid())
	{
		MessageEndpoint.Pin()->Publish(new FMultithreadingMessageLog(MessageLog), EMessageScope::Process);
	}
}
