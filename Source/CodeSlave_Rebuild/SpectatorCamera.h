// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "SpectatorCamera.generated.h"

/**
 * 
 */
UCLASS()
class CODESLAVE_REBUILD_API ASpectatorCamera : public ASpectatorPawn
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		class USceneComponent* scene;

	// Pawn's camera component
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
		class UCameraComponent* TopDownCameraComponent;

	// Camera Scroll boundary
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement Setting", meta = (AllowPrivateAccess = true))
		float CameraScrollBoundary;

	// Camera movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movement Setting", meta = (AllowPrivateAccess = true))
		float CameraPanningSpeed;

public:
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }


public:
	// constructor
	ASpectatorCamera();

	// Tick
	virtual void Tick(float DeltaSeconds) override;

	// BeginPlay
	virtual void BeginPlay() override;

private:

	FVector2D mouseOriginalPos;
	bool mouseMidButtonPressed;

	// camera moving functions
	void MoveCameraRight(float deltaMovement);

	void MoveCameraUp(float deltaMovement);

public:

	UFUNCTION(blueprintCallable)
	void DragCamera(FVector deltaPos);

	// toggle the boolean variable to indicate whether the mid mouse button is pressed
	UFUNCTION(blueprintCallable)
		void toggleMidButtonPress() { this->mouseMidButtonPressed = !this->mouseMidButtonPressed; }
	
	void updateOriginalMousePos();
	
};
