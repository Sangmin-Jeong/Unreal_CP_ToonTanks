// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();
	//UPROPERTY(Specifers) = Property Specifers
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite) // VisibleAnywhere = we can only see value anywhere in the default object's details panel
	//int32 VisibleAnywhereInt = 12;					// BlueprintReadWrite = In Viewport of BluePrint, we can read and write variable

	//UPROPERTY(EditAnywhere, BlueprintReadOnly) // EditAnywhere = we can see and edit value anywhere in the default object's details panel
	//int32 EditAnywhereInt = 22;					// BlueprintReadOnly = In Viewport of BluePrint, we can only read variable

	//UPROPERTY(VisibleInstanceOnly) // VisibleInstanceOnly = we can only see value in the object's details panel in Level
	//int32 VisibleInstanceOnlyInt = 11;

	//UPROPERTY(EditInstanceOnly, BlueprintReadOnly) // EditInstanceOnly = we can only see and edit value in the object's details panel in Level
	//int AmountOfBullets = 10;

	//UPROPERTY(VisibleDefaultsOnly) // VisibleDefaultsOnly = we can only see value in the default object's details panel
	//int32 VisibleDefaultsOnlyInt = 5;

	//UPROPERTY(EditDefaultsOnly) // EditDefaultsOnly = we can only see and edit value in the default object's details panel
	//int32 EditDefaultsOnlyInt = 9;



protected:

//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtTarget);
	void Fire();

private: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	int32 VisibleAnywhereIntP = 88;	//Category = "Name"  = The name of category in details panel
							//meta = (AllowPrivateAccess = "true") = we can only access variable in Unreal not C++ code

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	int32 EditAnywhereIntP = 77;

	// It is gonna allow us to have a C++ variable that represents a class type
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
