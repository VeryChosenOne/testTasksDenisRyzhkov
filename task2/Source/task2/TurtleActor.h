// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurtleActor.generated.h"

UCLASS()
class TASK2_API ATurtleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurtleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void PulsatingWorldOffset();

	UPROPERTY()
		UBoxComponent* Box;

	UPROPERTY()
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Particle;

	UPROPERTY()
		float FirstSpeed;

	UPROPERTY()
		float FirstSpeedDuration;

	UPROPERTY()
		float SecondSpeed;

	UPROPERTY()
		float SecondSpeedDuration;

	UPROPERTY()
		float Speed;

	UPROPERTY()
		bool FlipFlop;
};
