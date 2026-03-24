// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(0.f, 50.f, 50.f));

	for (int i = 0; i < 10; i++)
	{
		float RandomDistance = FMath::FRandRange(100.f, 300.f);
		float RandomAngle = FMath::FRandRange(-180.f, 180.f);

		Move(RandomDistance);
		Turn(RandomAngle);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("%d Count | Distance : %.2f | Angle : %.2f)"), i + 1, RandomDistance, RandomAngle));
		}
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Location : %s"), *CurrentLocation.ToString()));
	}

}

void AMyActor::Move(float Distance)
{
	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector NewLocation = CurrentLocation + (ForwardVector * Distance);

	SetActorLocation(NewLocation);
}

void AMyActor::Turn(float Angle)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += Angle;

	SetActorRotation(CurrentRotation);
}