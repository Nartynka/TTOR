// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTOR/Core/LevelEnum.h"

#include "Portal.generated.h"

UCLASS()
class TTOR_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELevels LevelName;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneRoot;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* aaa;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class UNiagaraComponent* PortalParticle;
};
