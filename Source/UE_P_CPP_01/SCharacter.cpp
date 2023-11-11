// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractComp = CreateDefaultSubobject<USInteractComponent>("InteractComp");

	AttributesComp = CreateDefaultSubobject<USArributesComponent>("AttributesComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot =  GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(),Value);
}
void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot =  GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RightVector =FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector,Value);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	/*if(ensure(ProjectileClass))
	{
		FVector RHandLoaction= GetMesh()->GetSocketLocation("Muzzle_01") + GetActorForwardVector()*0.5;
		/*FHitResult Hit;
		FVector Start,End;
		Start =
		FCollisionObjectQueryParams CollisionParam;
		GetWorld()->LineTraceSingleByObjectType(Hit,Start,End,CollisionParam);#1#
		
		FTransform SpawnTM = FTransform(GetControlRotation(),RHandLoaction);

		FActorSpawnParameters SpawnParams ;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
	
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);
	}*/
	SpawnProjectile(ProjectileClass);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_TimeElapsed,0.2f);
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
	
	
}

void ASCharacter::PrimaryInteract()
{
	if(InteractComp)
	{
		InteractComp->PrimaryInteract();
	}

}

void ASCharacter::PrimaryJump()
{
	Jump();
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("PrimaryJump",IE_Pressed,this,&ASCharacter::PrimaryJump);
}

void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if(ensureAlways(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator= this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams objParam;
		objParam.AddObjectTypesToQuery(ECC_WorldDynamic);
		objParam.AddObjectTypesToQuery(ECC_WorldStatic);
		objParam.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComp->GetComponentLocation();

		FVector TraceEnd= CameraComp->GetComponentLocation()+ (GetControlRotation().Vector() *5000);

		FHitResult Hit;
		if(GetWorld()->SweepSingleByObjectType(Hit,TraceStart,TraceEnd,FQuat::Identity,objParam,Shape,Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd-HandLocation).Rotator();
		FTransform SpawnTM = FTransform(ProjRotation,HandLocation);

		GetWorld()->SpawnActor<AActor>(ClassToSpawn,SpawnTM,SpawnParams);
		
		
		
	}
}
