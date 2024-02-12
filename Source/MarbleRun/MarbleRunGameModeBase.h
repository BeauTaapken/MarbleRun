// Copyright Beau Taapken. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MarbleRunGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MARBLERUN_API AMarbleRunGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;

	private:
		UFUNCTION()
		void PrintText();
	
		FTimerHandle WaitToSendMessage;
};
