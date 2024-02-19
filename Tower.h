// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ATower : public ABase_Pawn
{
	GENERATED_BODY()


public:
	ATower();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();//because we are going to call it in the game mode calss

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	private:
		class ATank* Tank;//forward declare

		UPROPERTY(EditDefaultsOnly,Category="Combat")
		float FireRange=500.f;
		//add collider for NPC

		 //add collider for NPC
		//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
			//class USphereComponent*  TriggerZone;
		FTimerHandle FireRateTimerHandle;//class and object for handling the timer function
		float FireRate=1.5f;
		void CheckFireCondition();
		bool InFireRange();
};
