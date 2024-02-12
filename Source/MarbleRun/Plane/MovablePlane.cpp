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
	InputComponent->BindAxis(TEXT("RotateDown"), this, &AMovablePlane::RotateDown);
	InputComponent->BindAxis(TEXT("RotateRight"), this, &AMovablePlane::RotateRight);
}

void AMovablePlane::RotateDown(float AxisValue)
{
	FRotator Rotation = FRotator(1.0f * AxisValue, 0.0f, 0.0f);
	AddActorWorldRotation(Rotation);
}

void AMovablePlane::RotateRight(float AxisValue)
{
	FRotator Rotation = FRotator(0.0f, 0.0f, 1.0f * AxisValue);
	AddActorWorldRotation(Rotation);
}


