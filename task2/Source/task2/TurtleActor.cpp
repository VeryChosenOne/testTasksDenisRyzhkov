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

	// �������� ��������� UBoxComponent
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	// �������� � ��������� USkeletalMeshComponenta, ��� ���������
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Box);
	Mesh->SetRelativeTransform(FTransform(FRotator(0, 90, 0), FVector(0, 0, 10), FVector(40, 40, 40)));

	// �������� � ��������� UParticle, ������ ������������
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(Box);
	Particle->SetRelativeLocation(FVector(-30, -20, 40));

	FlipFlop = true;
}

// Called when the game starts or when spawned
void ATurtleActor::BeginPlay()
{
	Super::BeginPlay();

	// ������ �������, ����� 0.01 ����� ��������� ���������, �������� ������� �������� ��������
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		ATurtleActor::PulsatingWorldOffset();
	}, 0.01f, false);
}

// Called every frame
void ATurtleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������������ ��������� �� ��������� Speed
	ATurtleActor::AddActorWorldOffset(FVector(0, Speed, 0));
}

// ������� �������� �������� ���������
void ATurtleActor::PulsatingWorldOffset()
{
	// ������ �������� ��������� � ������ �� ������ � �������
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

	// ����� ������� ������ SpeedDuration ������ ���� ��������� ����
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		if (IsValid(this))
		ATurtleActor::PulsatingWorldOffset();
	}, SpeedDuration, false);
}
