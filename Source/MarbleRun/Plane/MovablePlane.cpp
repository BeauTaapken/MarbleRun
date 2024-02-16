// Copyright Beau Taapken. All Rights Reserved.


#include "MovablePlane.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

AMovablePlane::AMovablePlane()
{
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	CollisionMesh->AttachToComponent(GetStaticMeshComponent(), FAttachmentTransformRules::KeepRelativeTransform, EndSocketName);
	CollisionMesh->InitBoxExtent(FVector(200, 200, 50));
}

void AMovablePlane::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInputComponent();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, "Welcome to my maze! How fast can you escape?");
}

void AMovablePlane::SetupPlayerInputComponent()
{
	InputComponent = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent was not set on MovablePlane"));
		return;
	}
	InputComponent->BindAxis(FName(TEXT("RotateDown")), this, &AMovablePlane::RotateDown);
	InputComponent->BindAxis(FName(TEXT("RotateRight")), this, &AMovablePlane::RotateRight);
	InputComponent->BindAction(FName(TEXT("Restart")), IE_Released, this, &AMovablePlane::Restart);
	InputComponent->BindAction(FName(TEXT("Exit")), IE_Released, this, &AMovablePlane::Quit);
}

void AMovablePlane::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!LevelWon)
	{
		LevelWon = true;
		FString BeatenInSeconds = FString::Printf(TEXT("%.2f"), GetWorld()->GetTimeSeconds());
		const FString WonMessage = FString("Well done! You escaped the maze in ").Append(BeatenInSeconds).Append(" seconds!");
	
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, TimeToWaitForLevelLoad, FColor::Orange, *WonMessage);
		}
		GetWorldTimerManager().SetTimer(WaitForLevelLoad, this, &AMovablePlane::LoadNextLevel, TimeToWaitForLevelLoad, false);	
	}
}

void AMovablePlane::RotateDown(float AxisValue)
{
	FRotator Rotation = this->GetActorRotation();
	Rotation.Pitch = FMath::Clamp(Rotation.Pitch + FMath::Clamp(RotationSpeed * AxisValue, -2.5f, 2.5f), -40.0f, 40.0f);
	this->SetActorRotation(Rotation, ETeleportType::TeleportPhysics);
}

void AMovablePlane::RotateRight(float AxisValue)
{
	FRotator Rotation = this->GetActorRotation();
	Rotation.Roll = FMath::Clamp(Rotation.Roll + FMath::Clamp(RotationSpeed * AxisValue, -2.5f, 2.5f), -40.0f, 40.0f);
	this->SetActorRotation(Rotation, ETeleportType::TeleportPhysics);
}
void AMovablePlane::Restart()
{
	// TODO get name of current level
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}

void AMovablePlane::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}

void AMovablePlane::LoadNextLevel()
{
	//TODO if ever continue, create a counting or random select?
	UGameplayStatics::OpenLevel(GetWorld(), LevelNames[0]);
	GetWorldTimerManager().ClearTimer(WaitForLevelLoad);
}
