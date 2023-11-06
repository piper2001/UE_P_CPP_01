// Fill out your copyright notice in the Description page of Project Settings.


#include "SExoplosiveBarrel.h"

#include "DrawDebugHelpers.h"

// Sets default values
ASExoplosiveBarrel::ASExoplosiveBarrel()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticComp");
	StaticMeshComp->SetSimulatePhysics(true);
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(StaticMeshComp);

	RadialForceComp->SetAutoActivate(false);

	RadialForceComp->Radius=750.0f;

	RadialForceComp->ForceStrength=2500.0f;

	RadialForceComp->bImpulseVelChange =true;

	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	
	
	
	
	

	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASExoplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExoplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMeshComp->OnComponentHit.AddDynamic(this,&ASExoplosiveBarrel::OnActorHit);
}

void ASExoplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp,Log,TEXT("OnActorHit in Explosive Barrel"));

	UE_LOG(LogTemp,Log,TEXT("OtherActor: %s, at game time: %f"),*GetNameSafe(OtherActor),GetWorld()->TimeSeconds);


	FString CombinedString = FString::Printf(TEXT("OtherActor: %s"),*Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(),Hit.ImpactPoint,CombinedString,nullptr,FColor::Green,2.0f,true);
		
}

// Called every frame
void ASExoplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

