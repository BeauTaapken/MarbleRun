// Copyright Beau Taapken. All Rights Reserved.


#include "MovablePlane.h"
#include "Components/InputComponent.h"

void AMovablePlane::BeginPlay()
{
	Super::BeginPlay();

	SetupPlayerInputComponent();
}

void AMovablePlane::SetupPlayerInputComponent()
{
	InputComponent = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent was not set on MovablePlane"))
		return;
	}
	InputComponent->BindAxis(FName(TEXT("RotateDown")), this, &AMovablePlane::RotateDown);
	InputComponent->BindAxis(FName(TEXT("RotateRight")), this, &AMovablePlane::RotateRight);
}

void AMovablePlane::RotateDown(float AxisValue)
{
	FRotator Rotation = this->GetActorRotation();
	Rotation.Pitch = FMath::Clamp(Rotation.Pitch + (RotationSpeed * AxisValue), -40.0f, 40.0f);
	this->SetActorRotation(Rotation, ETeleportType::TeleportPhysics);
}

void AMovablePlane::RotateRight(float AxisValue)
{
	FRotator Rotation = this->GetActorRotation();
	Rotation.Roll = FMath::Clamp(Rotation.Roll + (RotationSpeed * AxisValue), -40.0f, 40.0f);
	this->SetActorRotation(Rotation, ETeleportType::TeleportPhysics);
}


