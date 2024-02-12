// Copyright Beau Taapken. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovablePlane.generated.h"

/**
 * 
 */
UCLASS()
class MARBLERUN_API AMovablePlane : public AStaticMeshActor
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
	
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent();

	private:
		void RotateDown(float AxisValue);
		void RotateRight(float AxisValue);
		UPROPERTY(EditAnywhere, Category="Movement")
		int16 RotationSpeed = 1;
};
