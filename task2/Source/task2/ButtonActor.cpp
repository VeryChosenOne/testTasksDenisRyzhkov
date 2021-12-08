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

	// Создание корневого компонента
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Создание и настройка основания кнопки
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Root);
	Mesh->SetRelativeLocation(FVector(0, 0, -30));
	Mesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));

	// Создание и настройка кнопки
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->AttachTo(Root);
	ButtonMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	ButtonMesh->OnClicked.AddDynamic(this, &AButtonActor::OnButtonMeshClicked);

	// Создание и настройка эффекта, который будет вызываться при нажатии кнопки
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(Root);
	Particle->SetRelativeLocation(FVector(-50, 130, 0));
}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Ретекстур кнопки исходя из заданных параметров
	ButtonMesh->SetMaterial(0, ButtonMaterial);
	ButtonMesh->SetMaterial(1, NumberMaterial);
}

// Called every frame
void AButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Функция нажатия на кнопку, при нажатии кнопка опускается и после 0.1 секунды снова поднимается
//Нажатие на кнопку создает черепашку, которая идет вперед по заданным правилам
void AButtonActor::OnButtonMeshClicked(UPrimitiveComponent* Target, FKey ButtonPressed)
{
	ButtonMesh->SetRelativeLocation(FVector(0, 0, -10));

	//Активация эффекта и звука появлении черепашки
	Particle->Activate(true);
	UGameplayStatics::SpawnSoundAtLocation(this, Sound, Nest->GetActorLocation(), FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
	
	//Создание и настройка черепашки
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