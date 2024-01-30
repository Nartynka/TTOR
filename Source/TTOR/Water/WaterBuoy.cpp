// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterBuoy.h"

#include <Components/StaticMeshComponent.h>
#include <BuoyancyComponent.h>

AWaterBuoy::AWaterBuoy()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Buouancy = CreateDefaultSubobject<UBuoyancyComponent>(TEXT("Buouancy"));
	
}

void AWaterBuoy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterBuoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

