// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TurtleActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AButtonActor::AButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// �������� ��������� ����������
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// �������� � ��������� ��������� ������
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Root);
	Mesh->SetRelativeLocation(FVector(0, 0, -30));
	Mesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));

	// �������� � ��������� ������
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->AttachTo(Root);
	ButtonMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	ButtonMesh->OnClicked.AddDynamic(this, &AButtonActor::OnButtonMeshClicked);

	// �������� � ��������� �������, ������� ����� ���������� ��� ������� ������
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(Root);
	Particle->SetRelativeLocation(FVector(-50, 130, 0));
}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
	// ��������� ������ ������ �� �������� ����������
	ButtonMesh->SetMaterial(0, ButtonMaterial);
	ButtonMesh->SetMaterial(1, NumberMaterial);
}

// Called every frame
void AButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//������� ������� �� ������, ��� ������� ������ ���������� � ����� 0.1 ������� ����� �����������
//������� �� ������ ������� ���������, ������� ���� ������ �� �������� ��������
void AButtonActor::OnButtonMeshClicked(UPrimitiveComponent* Target, FKey ButtonPressed)
{
	ButtonMesh->SetRelativeLocation(FVector(0, 0, -10));

	//��������� ������� � ����� ��������� ���������
	Particle->Activate(true);
	UGameplayStatics::SpawnSoundAtLocation(this, Sound, Nest->GetActorLocation(), FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
	
	//�������� � ��������� ���������
	ATurtleActor* SpawnedTurtle = GetWorld()->SpawnActor<ATurtleActor>(Nest->GetActorLocation(), FRotator(0, 0, 0));
	SpawnedTurtle->FirstSpeed = FirstSpeed;
	SpawnedTurtle->FirstSpeedDuration = FirstSpeedDuration;
	SpawnedTurtle->SecondSpeed = SecondSpeed;
	SpawnedTurtle->SecondSpeedDuration = SecondSpeedDuration;
	SpawnedTurtle->Mesh->SetSkeletalMesh(TurtleMesh);
	SpawnedTurtle->Mesh->PlayAnimation(TurtleAnimation, true);
	SpawnedTurtle->Particle->SetTemplate(TurtleParticle);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		ButtonMesh->SetRelativeLocation(FVector(0, 0, 0));
	}, 0.1f, false);
}