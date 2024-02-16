// Copyright Beau Taapken. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/BoxComponent.h"
#include "MovablePlane.generated.h"

/**
 * 
 */
UCLASS()
class MARBLERUN_API AMovablePlane : public AStaticMeshActor
{
	GENERATED_BODY()

	public:
		AMovablePlane();
	
		virtual void BeginPlay() override;
	
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent();


		virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	private:
	// change to ULevelEndTrigger?
		UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* CollisionMesh;
	
		void RotateDown(float AxisValue);
		void RotateRight(float AxisValue);
		void Restart();
		void Quit();

		UFUNCTION()
		void LoadNextLevel();

		FTimerHandle WaitForLevelLoad;

		UPROPERTY(EditAnywhere, Category="Setup")
		float TimeToWaitForLevelLoad = 5.0f;
		UPROPERTY(EditAnywhere, Category="Setup")
		int16 RotationSpeed = 1;
		UPROPERTY(EditAnywhere, Category="Setup")
		FName EndSocketName = FName("End");
		UPROPERTY(EditAnywhere, Category="Setup")
		TArray<FName> LevelNames = {FName("Level1")};

		bool LevelWon = false;
};
