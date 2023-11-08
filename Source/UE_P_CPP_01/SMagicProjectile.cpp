// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include <Particles/ParticleSystemComponent.h>

#include "SArributesComponent.h"

//#include "AITypes.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	/*SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);*/
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	Effectcomp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	Effectcomp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationRemainsVertical = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	
	

}

void ASMagicProjectile::OnActorOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor &&  OtherActor!= GetInstigator())//加入对玩家（即发出魔法飞弹攻击的pwan）的排除
	{
		USArributesComponent* AttributesComp = Cast<USArributesComponent>(OtherActor->GetComponentByClass(USArributesComponent::StaticClass()));
		if(AttributesComp)
		{
			AttributesComp->ApplyHealthChange(-20.0f);

			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

