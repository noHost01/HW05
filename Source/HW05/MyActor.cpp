// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MoveCount = 0;
	EventCount = 0;
	TotalDistance = 0.f;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(0.f, 50.f, 50.f));

	int32 MaxMoveCount = 10;

	for (int i = 0; i < MaxMoveCount; i++)
	{
		float RandomDistance = FMath::FRandRange(100.f, 300.f);
		float RandomAngle = FMath::FRandRange(-180.f, 180.f);

		Turn(RandomAngle);
		Move(RandomDistance);

		// 50%확률 이벤트
		if (FMath::RandRange(0, 1) == 1)
		{
			TriggerEvent();
		}

		// 필수 기능 도전 기능시 너무 많은 로그가 찍힐수 있어서 주석 처리
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("%d Count | Distance : %.2f | Angle : %.2f)"), i + 1, RandomDistance, RandomAngle));
		}*/
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Total Travel Distance : %.2f"), TotalDistance));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Total Number of Events Occurring : %d"), EventCount));
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick도 똑같이 계속 찍히는 상황이라 주석처리
	/*FVector CurrentLocation = GetActorLocation();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Location : %s"), *CurrentLocation.ToString()));
	}*/
}

void AMyActor::Move(float Distance)
{
	FVector PreviousLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector NewLocation = PreviousLocation + (ForwardVector * Distance);

	SetActorLocation(NewLocation);

	float MovedDistance = FVector::Dist(PreviousLocation, NewLocation);
	TotalDistance += MovedDistance;

	MoveCount++;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("%d Count Move | current coordinates : %s"), MoveCount, *NewLocation.ToString()));
	}
}

void AMyActor::Turn(float Angle)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += Angle;

	SetActorRotation(CurrentRotation);
}

void AMyActor::TriggerEvent()
{
	EventCount++;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Event Live!"));
	}
}