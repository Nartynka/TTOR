// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TTOR/Player/HubCharacter/HubCharacter.h"
#include "TTOR/Core/TTORGameInstance.h"
#include "TTOR/Core/LevelEnum.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
#if WITH_EDITORONLY_DATA
	SceneRoot->bVisualizeComponent = true;
#endif
	RootComponent = SceneRoot;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());

	//PortalParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_Portal"));
	//PortalParticle->SetupAttachment(GetRootComponent());

}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnBoxOverlap);
}

void APortal::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AHubCharacter>(OtherActor))
	{
		if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
		{
			if (UTTORGameInstance* TTORGameInstance = Cast<UTTORGameInstance>(GameInstance))
			{
				if (TTORGameInstance->WasLevelCompleted(LevelName))
				{
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Already Completed"));
				}
				else
				{
#if WITH_EDITORONLY_DATA
					FString LevelName_str = UEnum::GetDisplayValueAsText(LevelName).ToString();
#else
					FString LevelName_str = UEnum::GetDisplayValueAsText(LevelName).ToString().RightChop(3);
#endif
					UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName_str));
				}
			}
		}
	}
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

