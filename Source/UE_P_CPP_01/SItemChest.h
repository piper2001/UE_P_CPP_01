// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"


	class UStaticMeshComponent;
UCLASS()
class UE_P_CPP_01_API ASItemChest : public AActor,public ISGamePlayInterface
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	
	void Interact_Implementation(APawn* InstigatorPawn) override;
	// Sets default values for this actor's properties
	ASItemChest();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
