// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor * DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false); // Game over
	}
	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers == 0)
		{
			GameOver(true); // Game still goes on
		}
		
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if(ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
																					// User Object        ,      Callback function						,  change bool
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

										//	Timer object         ,      Delegate             ,      Delay=3.0f,     for loop
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);


	}
	
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}
