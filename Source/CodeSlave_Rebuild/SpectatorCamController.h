// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpectatorCamController.generated.h"

/**
 * 
 */
UCLASS()
class CODESLAVE_REBUILD_API ASpectatorCamController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASpectatorCamController();
	
protected:
	virtual void SetupInputComponent() override;

private:
	void midMousePressed();

	void midMouseReleased();
};
