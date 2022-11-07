// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultithreadingGameModeBase.generated.h"

UCLASS()
class MULTITHREADING_API AMultithreadingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	TSharedPtr<class FMultithreadingMessagesController> MultithreadingMessagesController = nullptr;
};
