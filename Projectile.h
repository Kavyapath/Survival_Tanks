// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;
UCLASS()
class MYPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMovementComponent;  //speciall for the handling the movement of the projectile class
		
	//multicast delegate
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpluse,const FHitResult& Hit);//event overlap
	UPROPERTY(EditAnyWhere)
		float Damage = 50.f;
	UPROPERTY(EditAnyWhere,Category = "Combat")//for setting up the hitting effects
		class UParticleSystem* HitParticles;
	UPROPERTY(VisibleAnyWhere, Category = "Combat")//for smoke trail
		class UParticleSystemComponent* TrailParticles;
	UPROPERTY(Editanywhere, Category = "Combat")
		 USoundBase* LaunchSound;
	UPROPERTY(Editanywhere, Category = "Combat")
		USoundBase* HitSound;//already forward declare
	UPROPERTY(Editanywhere, Category = "Combat")//for camera Shake
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
