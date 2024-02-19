// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;//does not need to be true
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1500.f;
	ProjectileMovementComponent->InitialSpeed = 1500.f;
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeTrail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//we will perform hit event in begin play
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	//to play the sound at any location lauch sound would be play at the starting
	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void  AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit) {
	//UE_LOG(LogTemp,Warning,TEXT("OnHit"));

	AActor* MyOwner = GetOwner();//we set the owner in the base pawn class that is the blueprint projectile that we drived from this call and we need the instigator controller means the player controller who shot the projectile
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}


	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass=UDamageType::StaticClass();;
	//checkinf that
	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this,DamageTypeClass );//this for the projectile itself the damage causer and in the end we will pass damage type class
		if (HitParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());//first parameter is world context so we will pass this , second is Hit particle ,this function is for showing the fire hit effect at any location and rotation

		}
		//to play the sound at any location
		if (HitSound) {
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}//hit sound willl be played on hitting
		if (HitCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);//to  implement function below we need player controller so
		}
	}
	Destroy();
}

