// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SMagicProjectile.generated.h"

	class USphereComponent;
	class UProjectileMovementComponent;
	class UParticleSystemComponent;
	
UCLASS()
class UE_P_CPP_01_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere);
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere);
	UParticleSystemComponent* Effectcomp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
