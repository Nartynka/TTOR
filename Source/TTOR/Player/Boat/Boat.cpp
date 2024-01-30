// Fill out your copyright notice in the Description page of Project Settings.


#include "Boat.h"


#include <Components/InputComponent.h>
#include <Components/StaticMeshComponent.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>


ABoat::ABoat()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

}

void ABoat::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentHit.AddDynamic(this, &ABoat::OnHit);

	if (AController* PawnController = GetController())
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(PawnController))
		{
			if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
			{
				UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

				if (InputSubsystem)
				{
					InputSubsystem->AddMappingContext(InputContext, 0);
				}
			}
		}
	}
}

void ABoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0.f, RotationInput, 0.f));

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(515, 2.f, FColor::Red, FString::SanitizeFloat(RotationInput));
	//	GEngine->AddOnScreenDebugMessage(516, 2.f, FColor::Green, FString::SanitizeFloat(MoveInput));
	//	GEngine->AddOnScreenDebugMessage(517, 2.f, FColor::Blue, FString::SanitizeFloat(Motion));
	//}

	if (MoveInput)
	{
		Motion = FMath::Clamp(Motion + (MoveInput * ACCELERATION * DeltaTime), -MAX_SPEED, MAX_SPEED);
	}
	else
	{
		if(Motion > 0.f)
			Motion = FMath::Clamp(Motion - (FRICTION * DeltaTime), 0, MAX_SPEED);
		else
			Motion = FMath::Clamp(Motion + (FRICTION * DeltaTime), -MAX_SPEED, 0.f);
	}
	FVector FwVector = GetActorForwardVector();
	AddActorWorldOffset(FVector(FwVector.X * Motion, FwVector.Y * Motion, 0.f));
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABoat::Look);
		EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &ABoat::Accelerate);
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &ABoat::Steer);
		EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Completed, this, &ABoat::Accelerate);
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Completed, this, &ABoat::Steer);
	}
}

void ABoat::Look(const FInputActionValue& ActionValue)
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(2, 20.f, FColor::Emerald, FString("LookAround Func!"));
	//}
	//FVector2D ActionValue = Instance.GetValue().Get<FVector2D>();
	AddControllerYawInput(ActionValue.Get<FVector2D>().X);
}

void ABoat::Accelerate(const FInputActionValue& ActionValue)
{
	MoveInput = ActionValue.Get<float>();
}

void ABoat::Steer(const FInputActionValue& ActionValue)
{
	RotationInput = ActionValue.Get<float>();
}


void ABoat::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bDoOnce)
	{
		Motion = FMath::Clamp((KickbackForceMultiplyer * FMath::Sign(Motion)) * (Motion * Motion),
				-MAX_KICKBACK_FORCE, MAX_KICKBACK_FORCE);
		bDoOnce = false;

		FTimerHandle DoOnceTimer;
		GetWorldTimerManager().SetTimer(DoOnceTimer, [this]() {bDoOnce = true; }, 1.f, false);
	}
}