// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointTracker.h"
#include "Components/SplineComponent.h"
#include "WaterCheckpoint.h"
#include <Kismet/GameplayStatics.h>
#include "TTOR/Core/TTORGameInstance.h"

ACheckpointTracker::ACheckpointTracker()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
#if WITH_EDITORONLY_DATA
	SceneRoot->bVisualizeComponent = true;
#endif
	RootComponent = SceneRoot;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(GetRootComponent());

}


void ACheckpointTracker::BeginPlay()
{
	Super::BeginPlay();

	GenerateCheckpoints();
	ActivateCheckpoint();
}


void ACheckpointTracker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CheckpointTimer.IsValid() && GEngine)
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::SanitizeFloat(GetWorldTimerManager().GetTimerRemaining(CheckpointTimer)));

}


void ACheckpointTracker::GenerateCheckpoints()
{
	ClearCheckpoints();
	
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Orange, FString("Generating.."));
	
	if (!CheckpointClass)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("FAILED TO GENERATE CHECKPOINTS!\nReason: Checkpoint class was not specified!!"));
		UE_LOG(LogTemp, Error, TEXT("FAILED TO GENERATE CHECKPOINTS. Checkpoint class was not specified!!"));
		return;
	}

	for (int i = 0; i < Spline->GetNumberOfSplinePoints(); i++)
	{
		FVector SplinePoints = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);

		FVector CheckpointLocation = { SplinePoints.X, SplinePoints.Y,  SplinePoints.Z + 30.f };
		FRotator CheckpointRotation = Spline->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::World);

		AWaterCheckpoint* Checkpoint = Cast<AWaterCheckpoint>(GetWorld()->SpawnActor(CheckpointClass, &CheckpointLocation, &CheckpointRotation));
		Checkpoints.Add(Checkpoint);
	}
}


void ACheckpointTracker::ClearCheckpoints()
{
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString("Clearing.."), true);

 	TArray<AActor*> CheckpointsToDelete;
 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaterCheckpoint::StaticClass(), CheckpointsToDelete);
 
	for (AActor* Checkpoint : CheckpointsToDelete)
	{
		Checkpoint->Destroy();
	}
 
 	Checkpoints.Empty();
}


void ACheckpointTracker::ActivateCheckpoint()
{
	AWaterCheckpoint* Checkpoint = Checkpoints[ActiveCheckpoint];
	Checkpoint->OnCheckpointReachedDelegate.AddDynamic(this, &ACheckpointTracker::HandleCheckpointReached);
	Checkpoint->Activate();

	float Timeout = FMath::CeilToFloat((Spline->GetDistanceAlongSplineAtSplinePoint(ActiveCheckpoint) - Spline->GetDistanceAlongSplineAtSplinePoint(ActiveCheckpoint-1))/1000);
	GetWorldTimerManager().SetTimer(CheckpointTimer, this, &ACheckpointTracker::HandleGameOver, Timeout, false);
}


void ACheckpointTracker::HandleCheckpointReached()
{
	DeactivateCheckpoint();

	ActiveCheckpoint++;
	if (ActiveCheckpoint < Checkpoints.Num())
		ActivateCheckpoint();
	else
		HandleWin();
}

void ACheckpointTracker::DeactivateCheckpoint()
{
	GetWorldTimerManager().ClearTimer(CheckpointTimer);
	AWaterCheckpoint* Checkpoint = Checkpoints[ActiveCheckpoint];
	Checkpoint->OnCheckpointReachedDelegate.RemoveAll(this);
	Checkpoint->Deactivate();
}

void ACheckpointTracker::HandleWin()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, FString("YOU WIN!"));
	if (UTTORGameInstance* GameInstance = Cast<UTTORGameInstance>(GetGameInstance()))
	{
		GameInstance->CompleteLevel(ELevels::EL_Water);
	}
}

void ACheckpointTracker::HandleGameOver()
{
	DeactivateCheckpoint();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("GAME OVER! %u"), ActiveCheckpoint));
}

