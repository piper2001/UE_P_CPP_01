// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SArributesComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "STargetDummy.generated.h"


class USArributesComponent;
class UStaticMeshComponent;

UCLASS()
class UE_P_CPP_01_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTargetDummy();

protected:

	UPROPERTY(VisibleAnywhere)
	USArributesComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,USArributesComponent* OwningComp, float NewHealth,float Delta);
	


	


};
