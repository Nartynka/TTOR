// Fill out your copyright notice in the Description page of Project Settings.


#include "Storm.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "TTOR/Player/Boat/Boat.h"

AStorm::AStorm()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
#if WITH_EDITORONLY_DATA
	SceneRoot->bVisualizeComponent = true;
#endif
	RootComponent = SceneRoot;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());

	Lightning_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lightning_1"));
	Lightning_1->SetupAttachment(GetRootComponent());

	Lightning_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lightning_2"));
	Lightning_2->SetupAttachment(GetRootComponent());

}

void AStorm::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AStorm::OnBoxOverlap);

	FTimerHandle LightningTimer1;
	FTimerHandle LightningTimer2;

	GetWorldTimerManager().SetTimer(LightningTimer1, this, &AStorm::RandomPos1, 2.f, true);
	GetWorldTimerManager().SetTimer(LightningTimer2, this, &AStorm::RandomPos2, 4.f, true);

}

void AStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(FVector(10, 0, 0));
}

void AStorm::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABoat>(OtherActor))
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString("GAME OVER! You got struck by lightning"));
	}
}

void AStorm::RandomPos1()
{
	if (!Lightning_1)
	{
		UE_LOG(LogTemp, Error, TEXT("Lightning_1 pointer is not valid!!"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Lightning_1 pointer is not valid!!"));
		return;
	}

	Lightning_1->SetRelativeLocation(FVector(0.0, FMath::FRandRange(Lightning1_Min.X, Lightning1_Max.X), FMath::FRandRange(Lightning1_Min.Y, Lightning1_Max.Y)));
	Lightning_1->SetVisibility(true);

	GetWorldTimerManager().SetTimer(ResetVisibility1, [this]() {if (Lightning_1) Lightning_1->SetVisibility(false); }, 1.8f, false);
}

void AStorm::RandomPos2()
{
	if (!Lightning_2)
	{
		UE_LOG(LogTemp, Error, TEXT("Lightning_2 pointer is not valid!!"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Lightning_2 pointer is not valid!!"));
		return;
	}

	Lightning_2->SetRelativeLocation(FVector(0.0, FMath::FRandRange(Lightning2_Min.X, Lightning2_Max.X), FMath::FRandRange(Lightning2_Min.Y, Lightning2_Max.Y)));
	Lightning_2->SetVisibility(true);

	GetWorldTimerManager().SetTimer(ResetVisibility2, [this]() {if (Lightning_2) Lightning_2->SetVisibility(false);}, 3.8f, false);
}

void AStorm::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(ResetVisibility1);
	GetWorldTimerManager().ClearTimer(ResetVisibility2);
}
