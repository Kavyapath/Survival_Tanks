// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//#include "Components/SphereComponent.h"

ATank::ATank() {

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATank::Move(float Value) {
	FVector DeltaLocation(0.f);
	//X=Deltatime*Value*speed to control the framerate during movement because delta time is the difference between initially and final tick function call time

	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation,true);//for adding offset to character movement (for character movement),the second parameter is bsweep to stop our actor with overlaping anthor object(Actor) tick function
}
void ATank::Turn(float Value) {
	FRotator DeltaRotation = FRotator::ZeroRotator;
	//yaw=Deltatime*Value*turnspeed //like x,y,z yaw means we want rotation in the z axis
	DeltaRotation.Yaw= Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{ 
	Super::SetupPlayerInputComponent(PlayerInputComponent);//to call the parent constructor
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);//mapping input here
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this, &ATank::Fire);//IE_Pressed for the input
	//PlayerInputComponent->BindAction(TEXT("Interact"),IE_Pressed,this, &ATank::Interact);
	}

void ATank::BeginPlay() {
	Super::BeginPlay();//means calling all the begin pplay in the parent class
	PlayerControllerRef =Cast<APlayerController>(GetController()) ;//it retrun the type of Acontroller pointer which is not suitable for player controller
/*	DrawDebugSphere(GetWorld(),
		GetActorLocation() + FVector(0.f,0.f,200.f),// to make mouse curser movement in the game getting actor location  +FVector offset that at which distance we wank to move the curser in the x direction
	100.f,
	12,
	FColor::Red,
		true,
		 30.f);*/

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitResult;
	if (PlayerControllerRef) {
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		/*DrawDebugSphere(GetWorld(),
			HitResult.ImpactPoint,//GetActorLocation() + FVector(0.f, 0.f, 200.f),// to make mouse curser movement in the game getting actor location  +FVector offset that at which distance we wank to move the curser in the x direction
			25.f,
			12,
			FColor::Red,
			false,
			-1.f);*/

		RotateTurret(HitResult.ImpactPoint);
	}

}
void ATank::HandleDestruction() {
	Super::HandleDestruction();//so that the heatl destruction in all parent classes have been called so in this case pawn class is the parent class so visual and the sounds effects will be called
	SetActorHiddenInGame(true);// to hide our tank after its death
	SetActorTickEnabled(false);
	bAlive = false;
}