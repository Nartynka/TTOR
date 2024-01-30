// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Boat.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TTOR_API ABoat : public APawn
{
	GENERATED_BODY()

public:
	ABoat();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Rotation */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rotation")
	float RotationInput;

	/* Movement */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveInput;	 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float Motion = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float ACCELERATION = 7.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float FRICTION = 20.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MAX_SPEED = 60.f;

	/* Kickback */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kickback")
	float KickbackForceMultiplyer = -0.01; // Multiplier
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kickback")
	float MAX_KICKBACK_FORCE = 15.f;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool bDoOnce = true;

private:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMesh;

	/* Input */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AccelerateAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SteerAction;
	
	void Look(const FInputActionValue& ActionValue);
	void Accelerate(const FInputActionValue& ActionValue);
	void Steer(const FInputActionValue& ActionValue);

};
