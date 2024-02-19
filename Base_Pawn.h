// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Base_Pawn.generated.h"

UCLASS()
class MYPROJECT_API ABase_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABase_Pawn();

	void HandleDestruction();

	
protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComp;//forward declaration
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;//its header is include in default of unreal engine libraries
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly,Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;// to handle the blueprint that we created from the projectile class(it set this projectile class to a particular typed based on projectile it will include all the class and the blueprint that are derived from the projectile class)
	//now it become the variable of blueprint class type which we will futher use in the spawn actor function
	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* DeathParticles;
	UPROPERTY(Editanywhere, Category = "Combat")
		class USoundBase* DeathSound;
	UPROPERTY(Editanywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
