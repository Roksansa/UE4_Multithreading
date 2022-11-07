#pragma once

#include "CoreMinimal.h"
#include "MessageEndpoint.h"

DECLARE_STATS_GROUP(TEXT("SimpleRun"), STATGROUP_SimpleRun, STATCAT_Advanced);

class FSimpleRunnable : public FRunnable
{
public:
	FSimpleRunnable(FString& Id, int CurCount, TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> CurMessageEndpoint);

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

	void KillThread();

private:
	bool bStopThread = false;
	int32 Count;
	int32 CurStep;
	TUniquePtr<FRunnableThread> Thread;
	TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;
};
