// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

#include "SArributesComponent.h"
#include "SCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USInteractComponent;
class UAnimMontage;
class USArributesComponent;
UCLASS()
class UE_P_CPP_01_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	/*UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ClassToSpawn;*/
	
	UPROPERTY(EditAnywhere,Category="Attack");
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USInteractComponent* InteractComp;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USArributesComponent*  AttributesComp;
	// Called when the game starts or when spawned
	
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);


	void PrimaryAttack_TimeElapsed();
	
	void PrimaryAttack();
	void PrimaryInteract();
	void PrimaryJump();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
