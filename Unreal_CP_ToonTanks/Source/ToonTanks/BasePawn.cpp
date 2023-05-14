// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include <Components/CapsuleComponent.h>
//#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp; //  to make CapsuleComp be RootComponent

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp); // to attach
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual/sound effects
	if(DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}

	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}

	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
	
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	
	// There are two ways to regulate just Yaw
	
	//1
	//FRotator LookAtRotation = ToTarget.Rotation();
	//LookAtRotation.Pitch = 0.0f;
	//LookAtRotation.Roll = 0.0f;
	
	//2
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this), 
			15.0f)
	);
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPointLocation, 25.0f, 12, FColor::Red, false, 3.0f);

	// When Projectile is spawned, it will be declared as a own Actor
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	// And then Actor set the owner as the this(BasePawn)
	Projectile->SetOwner(this);

}

// Called when the game starts or when spawned
//void ABasePawn::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

//// Called every frame
//void ABasePawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	//FVector DeltaLocation(0.f);
//	//DeltaLocation.X = 2.f;
//	//AddActorLocalOffset(DeltaLocation);
//}

// Called to bind functionality to input
//void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

