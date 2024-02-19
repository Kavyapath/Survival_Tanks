// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABase_Pawn::ABase_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")); //and function to create any component by giving its type in template it is a template fun which will adapt to the type that we want
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);//to attach our mesh component to the capsule comp(root component)
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);


	
}

// Called when the game starts or when spawned


void ABase_Pawn::RotateTurret(FVector LookAtTarget) {
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw,0.f);//for settin the fRotator
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			200.f));
}

// Called to bind functionality to input
void ABase_Pawn::Fire() {
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();//function and the object to find the location of the projectile launch
/*	DrawDebugSphere(
		GetWorld(),//world component pointer
		ProjectileSpawnLocation,//Location at which debug sphere is drawnn
		25.f,
		12,
		FColor::Blue,
		false,
		3.f//life time of debug sphere
	);
*/
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	//now instead of our debug sphere our projectile will be launching whwn we click on the left fire button
	//now we want to spawn the projectile class as the actor
	AProjectile* Projectile=GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);//ProjectileClass is the Uclass(blueprint type) that we created using tsubclass<projectile> () that will be the first parameter of this
	Projectile->SetOwner(this);//setting the owner for of the projectile this means itself him
}

void ABase_Pawn::HandleDestruction() {
	//todo Sound effects and visuals
	if (DeathParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());//this for world context object ,2 nd for death particles 
	}
	//to play the sound at any location
	if (DeathSound) {
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass) {
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);//for camera shake
	}
}