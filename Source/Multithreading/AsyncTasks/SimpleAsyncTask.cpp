#include "SimpleAsyncTask.h"

#include "Messages/MessagesController.h"


FSimpleAsyncTask::FSimpleAsyncTask(FString& Id, int32 CurCount, TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> CurMessageEndpoint)
	: CurStep(0), Count(CurCount), Name(Id), MessageEndpoint(CurMessageEndpoint)
{
}

void FSimpleAsyncTask::DoWork()
{
	//Calculating the prime numbers...
	for (CurStep = 1; CurStep <= Count; CurStep++)
	{
		bool bIsPrime = true;
		const int Div = CurStep * 0.5f;
		for (int32 j = 2; j <= Div; j++)
		{
			if (CurStep % j == 0)
			{
				bIsPrime = false;
				break;
			}
		}

		if (bIsPrime)
		{
			FPlatformProcess::Sleep(0.f);
		}
	}

	const FString MessageLog = "Prime number " + FString::FromInt(CurStep) + ": " + Name + " : " + FString::FromInt(Count);
	FMultithreadingMessagesController::PublishMultithreadingMessageLog(MessageEndpoint, MessageLog);

	MessageEndpoint.Reset();
}
