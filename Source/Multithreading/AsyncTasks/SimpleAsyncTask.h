#pragma once
#include "MessageEndpoint.h"

class FSimpleAsyncTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FSimpleAsyncTask>;

public:
	FSimpleAsyncTask(FString& Id, int32 CurCount, TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> CurMessageEndpoint);

protected:
	void DoWork();
	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FSimpleAsyncTask, STATGROUP_ThreadPoolAsyncTasks); }

private:
	int32 CurStep;
	int32 Count;
	FString Name;

	TWeakPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;
};
