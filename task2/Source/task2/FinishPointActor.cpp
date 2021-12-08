// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishPointActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinishPointActor::AFinishPointActor(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Создание корневого UBoxComponent, при взаимодействии с которым срабатывает функция OnFinishPointActorOverlap
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->OnComponentBeginOverlap.AddDynamic(this, &AFinishPointActor::OnFinishPointActorOverlap);

	// Создание и настройка модели точки назначения
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Box);
	Mesh->SetRelativeTransform(FTransform(FRotator(0, FMath::RandRange(0.0f, 359.0f), 0), FVector(FMath::RandRange(-20.0f,20.0f), FMath::RandRange(-20.0f, 20.0f), 0), FVector(0.5f, 0.5f, 0.5f)));
	
	// Создание и настройка эффекта, который вызывается на точке назначения
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(Box);
	Particle->SetRelativeScale3D(FVector(2, 2, 2));
}

// Called when the game starts or when spawned
void AFinishPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Функция срабатывает, когда черепашка сталкивается с точкой назначения
// Она уничтожает актора, который с ней сталкивается, а также активирует эффект и звук
void AFinishPointActor::OnFinishPointActorOverlap(UPrimitiveComponent*, class AActor* OtherActor, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	OtherActor->Destroy();
	Particle->Activate(true);
	UGameplayStatics::SpawnSoundAtLocation(this, Sound, this->GetActorLocation(), FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
}