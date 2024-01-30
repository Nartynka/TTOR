// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointTracker.generated.h"

UCLASS()
class TTOR_API ACheckpointTracker : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckpointTracker();

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	void HandleGameOver();
	void HandleWin();
private:
	UPROPERTY(EditAnywhere, Category = "Checkpoints")
	UClass* CheckpointClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Checkpoints", meta = (AllowPrivateAccess))
	TArray<class AWaterCheckpoint*> Checkpoints;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Checkpoints", DisplayName = "Active Checkpoint Index", meta = (AllowPrivateAccess))
	int32 ActiveCheckpoint = 0;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	FTimerHandle CheckpointTimer;

	/* Functions */
	UFUNCTION(BlueprintCallable)
	void GenerateCheckpoints();

	UFUNCTION(BlueprintCallable)
	void ClearCheckpoints();

	UFUNCTION(BlueprintCallable)
	void ActivateCheckpoint();

	UFUNCTION(BlueprintCallable)
	void DeactivateCheckpoint();

	UFUNCTION()
	void HandleCheckpointReached();


	/* Components */
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class USplineComponent* Spline;
};
