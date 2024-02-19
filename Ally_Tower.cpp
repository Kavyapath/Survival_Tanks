// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally_Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"


AAlly_Tower::AAlly_Tower() {
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
}

//we want tower turret to move so we will create tick function
void AAlly_Tower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//find the distance to the tank
	if (Tank) {
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());


		//Check to see that that tank is in the range
		if (Distance <= FireRange) {
			//if in a range tower turrent toward tank
		//best place to get hold of tank is in begin play
			RotateTurret(Tank->GetActorLocation());//we need the location of the actor or pawn at which our turret is moving
		}

	}

}
void AAlly_Tower::BeginPlay() {
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));//to get the tank pawn in the code //tank is the child class of Apawn so the return value pointer is inappropriate so we have to cast it


}

/*void  AAlly_Tower::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor is : %s"),*OtherActor->GetName());
	GEngine->AddOnScreenDebugMessage(-1,20.0f,FColor::Blue,TEXT("Drone tower in the centre is hacked "));
	DrawDebugSphere(GetWorld(),
		GetActorLocation() + FVector(0.f, 0.f, 200.f),// to make mouse curser movement in the game getting actor location  +FVector offset that at which distance we wank to move the curser in the x direction
		100.f,
		12,
		FColor::Red,
		true,
		30.f);
}*/