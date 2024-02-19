// Fill out your copyright notice in the Description page of Project Settings.


#include "TOONTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void ATOONTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled) {
	if (bPlayerEnabled) {//we need to get the pawn if enabling or disabling its controller
		GetPawn()->EnableInput(this);
	}
	else {
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}