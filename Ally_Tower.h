// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pawn.h"
#include "Ally_Tower.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AAlly_Tower : public ABase_Pawn
{
	GENERATED_BODY()
public:
	AAlly_Tower();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* Tank;//forward declare

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float FireRange = 1000.f;
   UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box; 



};
