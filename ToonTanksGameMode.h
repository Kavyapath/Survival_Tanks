// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);//it is public because it is going to be called in the health component

protected:
		virtual void BeginPlay() override;
		UFUNCTION(BlueprintImplementableEvent)
			void StartGame();
		UFUNCTION(BlueprintImplementableEvent)
			void GameOver(bool bWonGame);
 private:
	class ATank* Tank;
	class ATOONTanksPlayerController* ToonTanksPlayerController;
	float StartDelay = 3.0f;

	//timer function for delay

	void HandleGameStart();
	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();
};
