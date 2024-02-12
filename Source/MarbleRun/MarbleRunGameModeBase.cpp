// Copyright Beau Taapken. All Rights Reserved.


#include "MarbleRunGameModeBase.h"

void AMarbleRunGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(WaitToSendMessage, this, &AMarbleRunGameModeBase::PrintText, 2, false);
}

void AMarbleRunGameModeBase::PrintText()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("testing my magic code"));
	}
	GetWorldTimerManager().ClearTimer(WaitToSendMessage);
}

