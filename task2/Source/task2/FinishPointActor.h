// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishPointActor.generated.h"

UCLASS()
class TASK2_API AFinishPointActor : public AActor
{

	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFinishPointActor(const FObjectInitializer& objectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnFinishPointActorOverlap(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY()
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere)
		USoundWave* Sound;
};
