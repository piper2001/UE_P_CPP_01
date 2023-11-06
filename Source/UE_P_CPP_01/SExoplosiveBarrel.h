// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"

#include "Components/StaticMeshComponent.h"
#include "SExoplosiveBarrel.generated.h"
class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class UE_P_CPP_01_API ASExoplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;
	
	

	
	// Sets default values for this actor's properties
	ASExoplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorHit ( UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);

	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
