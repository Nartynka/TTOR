// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterBuoy.generated.h"

UCLASS()
class TTOR_API AWaterBuoy : public AActor
{
	GENERATED_BODY()
	
public:	
	AWaterBuoy();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	class UBuoyancyComponent* Buouancy;
};
