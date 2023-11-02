// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractComponent.h"

#include "DrawDebugHelpers.h"
#include "SGamePlayInterface.h"

// Sets default values for this component's properties
USInteractComponent::USInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USInteractComponent::PrimaryInteract()
{

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner= GetOwner();

	//FVector Start;


	FVector Eyelocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(Eyelocation,EyeRotation);
	
	FVector End = Eyelocation + (EyeRotation.Vector()*1000);
	



	//FHitResult Hit;

	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit,Eyelocation,End,ObjectQueryParams);


	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	float Radius = 30.0f;
	Shape.SetSphere(Radius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits,Eyelocation,End,FQuat::Identity,ObjectQueryParams,Shape);

	FColor LineColor = bBlockingHit?FColor::Green : FColor::Red;
	for(FHitResult Hit : Hits)
	{
		AActor* HitActor= Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USGamePlayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
			
				ISGamePlayInterface::Execute_Interact(HitActor,MyPawn);
				DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,LineColor,false ,2.0f);
				break;
			}
			
		}
	}
	

	
	DrawDebugLine(GetWorld(),Eyelocation,End,LineColor,false,2.0f,0,2.0f);

	
	
}


// Called when the game starts
void USInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

