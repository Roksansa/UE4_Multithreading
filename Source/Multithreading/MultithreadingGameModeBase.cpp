// Copyright Epic Games, Inc. All Rights Reserved.


#include "MultithreadingGameModeBase.h"
#include "Messages/MessagesController.h"

void AMultithreadingGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	MultithreadingMessagesController = MakeShareable(new FMultithreadingMessagesController());
	MultithreadingMessagesController->Startup();
}
