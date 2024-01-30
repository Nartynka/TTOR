// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateCombinations.h"

#include "WaterCheckpoint.generated.h"

class UChildActorComponent;

UCLASS()
class TTOR_API AWaterCheckpoint : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCheckpointReached);

public:
	AWaterCheckpoint();

	UPROPERTY(BlueprintAssignable)
	FCheckpointReached OnCheckpointReachedDelegate;

	virtual void Tick(float DeltaTime) override;
	
	void Activate();
	void Deactivate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void GreyOutCones();
	void GrayOutCone(UChildActorComponent* WaterBuoy);

private:
	bool bIsActive = false;
	
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	UMaterial* GrayMaterial;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneRoot;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "NS_Checkpoint", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* CheckpointParticle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* WaterBuoy_1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* WaterBuoy_2;


};
