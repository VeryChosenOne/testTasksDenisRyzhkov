// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonActor.generated.h"

UCLASS()
class TASK2_API AButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnButtonMeshClicked(UPrimitiveComponent* Target, FKey ButtonPressed);

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ButtonMesh;

	UPROPERTY(EditAnywhere)
		UMaterialInstance* ButtonMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInstance* NumberMaterial;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere)
		USoundWave* Sound;

	UPROPERTY(EditAnywhere)
		AActor* Nest;

	UPROPERTY(EditAnywhere)
		USkeletalMesh* TurtleMesh;

	UPROPERTY(EditAnywhere)
		UAnimationAsset* TurtleAnimation;

	UPROPERTY(EditAnywhere)
		UParticleSystem* TurtleParticle;

	UPROPERTY(EditAnywhere)
		float FirstSpeed;

	UPROPERTY(EditAnywhere)
		float FirstSpeedDuration;
	
	UPROPERTY(EditAnywhere)
		float SecondSpeed;

	UPROPERTY(EditAnywhere)
		float SecondSpeedDuration;
};
