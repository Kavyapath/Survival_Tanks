// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
//#include "Components/SphereComponent.h"


ATower::ATower() {
	//TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	//TriggerZone->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//TriggerZone->SetSphereRadius(200.f);
}

//we want tower turret to move so we will create tick function
void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//find the distance to the tank
	if (InFireRange()) {
		//float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());


		//Check to see that that tank is in the range
		
			//if in a range tower turrent toward tank
		//best place to get hold of tank is in begin play
			RotateTurret(Tank->GetActorLocation());//we need the location of the actor or pawn at which our turret is moving
		 
		
	}

}
void ATower::HandleDestruction() {
	Super::HandleDestruction();//so that the heatl destruction in all parent classes have been called so in this case pawn class is the parent class so visual and the sounds effects will be called
	Destroy();
}
void ATower::BeginPlay() {
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));//to get the tank pawn in the code //tank is the child class of Apawn so the return value pointer is inappropriate so we have to cast it
//to Hnadle the object of and get the access of the FTimerHandle class
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition,FireRate,true);//3rd input is the callback function and  last input for the looping and we want to call the function at every interval of 2 sec
}
void ATower::CheckFireCondition() {

	if (Tank == nullptr) {
		return;
	}
	if (InFireRange() && Tank->bAlive) {
			Fire();//we need the location of the actor or pawn at which our turret is moving
		

	}
}
 bool ATower::InFireRange(){
	if (Tank) {
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());


		//Check to see that that tank is in the range
		if (Distance <= FireRange) {
			//if in a range tower turrent toward tank
		//best place to get hold of tank is in begin play
			return true;;//we need the location of the actor or pawn at which our turret is moving
		}
	
	}
	return false;
}