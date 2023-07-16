// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterCheckpoint.h"

// Sets default values
AWaterCheckpoint::AWaterCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaterCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

