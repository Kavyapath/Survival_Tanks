// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ATank : public ABase_Pawn
{
	GENERATED_BODY()

public:
	ATank();
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const {
		return PlayerControllerRef;
	}
	bool bAlive = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
		UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* Camera;//forward declare them

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;
	//add collider for NPC
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		//class USphereComponent* Sphere; 
	

	UPROPERTY(EditAnywhere, Category = "Movements")
		float Speed = 1000.f;
	UPROPERTY(EditAnywhere, Category = "Movements")
		float TurnRate = 200.f;

	void Move(float Value);
	void Turn(float Value);
	APlayerController* PlayerControllerRef;
};
