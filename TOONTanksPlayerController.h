// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TOONTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ATOONTanksPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
		void SetPlayerEnabledState(bool bPlayerEnabled);
};
