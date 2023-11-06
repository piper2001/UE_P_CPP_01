// Fill out your copyright notice in the Description page of Project Settings.


#include "SArributesComponent.h"

// Sets default values for this component's properties
USArributesComponent::USArributesComponent()
{


	Health=100;
	// ...
}







bool USArributesComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr,this,Health,Delta);
	return true;
}

