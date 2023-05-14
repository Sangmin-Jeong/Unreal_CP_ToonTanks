// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	//RootComponent = SpringArmComp;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Speed = 500.0f;
	TurnRate = 90.0;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.0f, 12, FColor::Red, false);
		RotateTurret(HitResult.ImpactPoint);
		
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true); // Hide
	SetActorTickEnabled(false); // Disable Ticking
	bAlive = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//AContoroller is higher class than APlayerController, so we need to cast them
	TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::Move(float Value)
{
	//  to print the text on Output Log window
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value); 

	FVector DeltaLocation(0.0f); // or FVector DeltaLocation = FVector::ZeroVector; to set up all axis value to 0
	// X = Value * DeltaTime * Speed
	DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	DeltaLocation.Y = 0.0f;		
	DeltaLocation.Z = 0.0f;

	//AddActorLocalOffset(FVector) = Adds a delta to the location of this component in its local reference frame.
	AddActorLocalOffset(DeltaLocation, true); 
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	
	// Yaw = (Z) = Value * DeltaTime * TurnRate
	DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;

	AddActorLocalRotation(DeltaRotation, true);

}

