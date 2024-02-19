// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TOONTanksPlayerController.h"


void AToonTanksGameMode::BeginPlay() {
	
	Super::BeginPlay();
	HandleGameStart();//now this is responsible for casting and initializing the value of required pointer 


}
void AToonTanksGameMode::HandleGameStart() {

	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));//it return a pawn pointer than we have to cast in to the tank Actor class pointer
	ToonTanksPlayerController = Cast<ATOONTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	StartGame();
	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		//for timer controller we have to create the ftimercontroller variable
		FTimerHandle PlayerEnabledTimerHandle;
		FTimerDelegate PlayerEnabedTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,//First parameter is the player controller
			& ATOONTanksPlayerController::SetPlayerEnabledState,//call back function for timer delegate
			true//value that we want to pass we make true in setplayerenabled state

		);
		GetWorldTimerManager().SetTimer(
		PlayerEnabledTimerHandle,//ftimerhandle 
			PlayerEnabedTimerDelegate,//Delegate that we just created above
			StartDelay,//Delay time
		  false//Looping condition
		);
	}
}
void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		if (ToonTanksPlayerController) {

			//Now in the game mode class we are setting up the player controller using object of TOONTanksPlayercontroller class
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyTower = Cast<ATower>(DeadActor)) {
		DestroyTower->HandleDestruction();
		--TargetTowers;//after killin towers we are decreasing their values
		if (TargetTowers == 0) {
			GameOver(true);
		}
	}
}
int32 AToonTanksGameMode::GetTargetTowerCount() {
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);//to store all the tower actor in a single array
	return Towers.Num();
}