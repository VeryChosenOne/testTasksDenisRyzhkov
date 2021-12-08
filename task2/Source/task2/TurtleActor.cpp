// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleActor.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATurtleActor::ATurtleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Создание корневого UBoxComponent
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	// Создание и настройка USkeletalMeshComponenta, Меш черепашки
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Box);
	Mesh->SetRelativeTransform(FTransform(FRotator(0, 90, 0), FVector(0, 0, 10), FVector(40, 40, 40)));

	// Создание и настройка UParticle, Эффект передвижения
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(Box);
	Particle->SetRelativeLocation(FVector(-30, -20, 40));

	FlipFlop = true;
}

// Called when the game starts or when spawned
void ATurtleActor::BeginPlay()
{
	Super::BeginPlay();

	// Запуск таймера, через 0.01 после появления черепашки, вызывает функцию рассчета скорости
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		ATurtleActor::PulsatingWorldOffset();
	}, 0.01f, false);
}

// Called every frame
void ATurtleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Передвижение черепашки со скоростью Speed
	ATurtleActor::AddActorWorldOffset(FVector(0, Speed, 0));
}

// Функция рассчета скорости черепашки
void ATurtleActor::PulsatingWorldOffset()
{
	// Меняет скорость черепашки с первой на вторую и обратно
	float SpeedDuration;
	if (FlipFlop)
	{
		Speed = FirstSpeed;
		SpeedDuration = FirstSpeedDuration;
	}
	else
	{
		Speed = SecondSpeed;
		SpeedDuration = SecondSpeedDuration;
	}
	Mesh->SetPlayRate(Speed * 4);
	FlipFlop = !FlipFlop;

	// Вызов таймера каждые SpeedDuration секунд пока черепашка жива
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		if (IsValid(this))
		ATurtleActor::PulsatingWorldOffset();
	}, SpeedDuration, false);
}
