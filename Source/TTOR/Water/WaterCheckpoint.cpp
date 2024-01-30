// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterCheckpoint.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "TTOR/Player/Boat/Boat.h"
#include "Components/ChildActorComponent.h"
#include "WaterBuoy.h"

AWaterCheckpoint::AWaterCheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
#if WITH_EDITORONLY_DATA
	SceneRoot->bVisualizeComponent = true;
#endif
	RootComponent = SceneRoot;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
 	Box->SetupAttachment(GetRootComponent());

	CheckpointParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_Checkpoint"));
 	CheckpointParticle->SetupAttachment(GetRootComponent());

	WaterBuoy_1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("WaterBuoy_1"));
	WaterBuoy_1->SetupAttachment(GetRootComponent());

	WaterBuoy_2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("WaterBuoy_2"));
	WaterBuoy_2->SetupAttachment(GetRootComponent());

}

void AWaterCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AWaterCheckpoint::OnBoxOverlap);

}

void AWaterCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaterCheckpoint::Activate()
{
	bIsActive = true;
	CheckpointParticle->Activate();
}

void AWaterCheckpoint::Deactivate()
{
	bIsActive = false;
	CheckpointParticle->Deactivate();

	GreyOutCones();
}

void AWaterCheckpoint::GreyOutCones()
{
	if (!GrayMaterial)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("FAILED TO GRAYOUT CHECKPOINT!\nReason: Checkpoint Gray Material was not specified!!"));
		UE_LOG(LogTemp, Error, TEXT("FAILED TO GRAYOUT CHECKPOINT!\nReason: Checkpoint Gray Material was not specified!!"));
		return;
	}

	GrayOutCone(WaterBuoy_1);
	GrayOutCone(WaterBuoy_2);

}

void AWaterCheckpoint::GrayOutCone(UChildActorComponent* WaterBuoy)
{
	AWaterBuoy* WaterBuoyChild = Cast<AWaterBuoy>(WaterBuoy->GetChildActor());
	if (WaterBuoyChild)
	{
		UStaticMeshComponent* BuoyMesh = WaterBuoyChild->GetComponentByClass<UStaticMeshComponent>();
		if (BuoyMesh)
			BuoyMesh->SetMaterial(0, GrayMaterial);
	}
}

void AWaterCheckpoint::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bIsActive)
	{
		if(Cast<ABoat>(OtherActor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString("Checkpoint!"));
			bIsActive = false;
			OnCheckpointReachedDelegate.Broadcast();
		}
	}
}

