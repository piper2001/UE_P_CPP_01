// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SArributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,AActor*,InstigatorActor,USArributesComponent*,OwningComp,float,NewHealth,float,Delta);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_P_CPP_01_API USArributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USArributesComponent();

protected:

	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attributes")
	float Health;




public:	

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(float Delta);
		
};
