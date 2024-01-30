// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Storm.generated.h"

class UStaticMeshComponent;

UCLASS()
class TTOR_API AStorm : public AActor
{
	GENERATED_BODY()
	
public:	
	AStorm();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Lightnings Random Position Range")
	FVector2D Lightning1_Min = { -1500.0, -800.0 };
	UPROPERTY(EditAnywhere, Category = "Lightnings Random Position Range")
	FVector2D Lightning1_Max = { -200.0, -900.0 };

	UPROPERTY(EditAnywhere, Category = "Lightnings Random Position Range")
	FVector2D Lightning2_Min = { 100.0, -800.0 };
	UPROPERTY(EditAnywhere, Category = "Lightnings Random Position Range")
	FVector2D Lightning2_Max = { 1500.0, -900.0 };

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle ResetVisibility1;
	FTimerHandle ResetVisibility2;

	void RandomPos1();
	void RandomPos2();


private:
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Lightning_1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Lightning_2;

};
