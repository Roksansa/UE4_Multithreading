#include "SimpleRunnable.h"

#include "MessageEndpoint.h"
#include "MessageEndpointBuilder.h"
#include "Messages/MessagesController.h"

//считает все затраченное время
DECLARE_CYCLE_STAT(TEXT("SimpleRun ~ Run"), STAT_Run, STATGROUP_SimpleRun);

FSimpleRunnable::FSimpleRunnable(FString& Id, int CurCount, TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> CurMessageEndpoint)
{
	Count = CurCount;
	Thread = TUniquePtr<FRunnableThread>(
		FRunnableThread::Create(this, *FString::Printf(TEXT("FSimpleRunnable____%s"), *Id), 0, TPri_BelowNormal));
	MessageEndpoint = CurMessageEndpoint;
}

bool FSimpleRunnable::Init()
{
	return FRunnable::Init();
}

uint32 FSimpleRunnable::Run()
{
	//Calculating the prime numbers...
	for (CurStep = 1; CurStep <= Count && !bStopThread; CurStep++)
	{
		bool isPrime = true;
		SCOPE_CYCLE_COUNTER(STAT_Run);
		for (int32 j = 2; j <= CurStep / 2; j++)
		{
			if (CurStep % j == 0)
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime /* && Thread.IsValid()*/)
		{
			FPlatformProcess::Sleep(0.f);
		}
	}
	if (Thread.IsValid())
	{
		FString MessageLog = "Prime number " + FString::FromInt(CurStep) + ": " + Thread.Get()->GetThreadName() + ": " +
		                     FString::FromInt(Count);

		FMultithreadingMessagesController::PublishMultithreadingMessageLog(MessageEndpoint, MessageLog);

		if (bStopThread)
		{
			MessageLog = "Prime number " + FString::FromInt(CurStep) + ": STOOOP" + ": " + FString::FromInt(Count);
			FMultithreadingMessagesController::PublishMultithreadingMessageLog(MessageEndpoint, MessageLog);
		}
	}
	return 0;
}

void FSimpleRunnable::Exit()
{
	FRunnable::Exit();
}

void FSimpleRunnable::Stop()
{
	bStopThread = true;
	MessageEndpoint.Reset();
	FRunnable::Stop();
}

void FSimpleRunnable::KillThread()
{
	if (Thread.IsValid())
	{
		Thread->Kill();
	}
}
