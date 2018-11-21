// Fill out your copyright notice in the Description page of Project Settings.

#include "SpectatorCamera.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameViewportClient.h"
#include "Engine.h"

ASpectatorCamera::ASpectatorCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	this->scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->scene;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	TopDownCameraComponent->OrthoWidth = 720.0f;
	TopDownCameraComponent->SetupAttachment(RootComponent);

	TopDownCameraComponent->bUsePawnControlRotation = false;
	TopDownCameraComponent->bAutoActivate = true;

	TopDownCameraComponent->AspectRatio = (double)(38 / 30);

	this->CameraScrollBoundary = 50.0f;
	this->CameraPanningSpeed = 80.0f;

	this->mouseMidButtonPressed = false;

}

void ASpectatorCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector2D mousePos;
	FVector2D viewportSize;

	UGameViewportClient* viewport = GEngine->GameViewport;

	check(viewport);

	viewport->GetViewportSize(viewportSize);

	// when viewport is focused
	if (viewport->IsFocused(viewport->Viewport) && viewport->GetMousePosition(mousePos))
	{
		if (!this->mouseMidButtonPressed) 
		{
			// left and right boundary check
			if (mousePos.X < CameraScrollBoundary) 
			{
				// move left
				this->MoveCameraRight(-1.0f * this->CameraPanningSpeed * DeltaSeconds);
			}
			else if (viewportSize.X - mousePos.X < CameraScrollBoundary) 
			{
				this->MoveCameraRight(1.0f * this->CameraPanningSpeed * DeltaSeconds);
			}

			// top and bottom boundary check

			if (mousePos.Y < CameraScrollBoundary) 
			{
				this->MoveCameraUp(-1.0f * this->CameraPanningSpeed * DeltaSeconds);
			}
			else if (viewportSize.Y - mousePos.Y < CameraScrollBoundary) 
			{
				this->MoveCameraUp(1.0f * this->CameraPanningSpeed * DeltaSeconds);
			}
		}
		else 
		{
			FVector2D deltaMovement = mouseOriginalPos - mousePos;
			FVector deltaPos = FVector(deltaMovement.X, deltaMovement.Y, 0.0f);
			DragCamera(deltaPos);
			mouseOriginalPos = mousePos;
		}
	}
}

void ASpectatorCamera::BeginPlay()
{
	Super::BeginPlay();
}

void ASpectatorCamera::MoveCameraRight(float deltaMovement)
{
	FVector deltaMov = deltaMovement * FVector(1.0f, 0.0f, 0.0f);

	FVector newLocation = this->GetActorLocation() + deltaMov;
	SetActorLocation(newLocation);
}

void ASpectatorCamera::MoveCameraUp(float deltaMovement)
{
	FVector deltaMov = deltaMovement * FVector(0.0f, 1.0f, 0.0f);

	FVector newLocation = this->GetActorLocation() + deltaMov;
	SetActorLocation(newLocation);
}

void ASpectatorCamera::DragCamera(FVector deltaPos)
{
	FVector newLocation = this->GetActorLocation() + deltaPos;
	SetActorLocation(newLocation);
}

void ASpectatorCamera::updateOriginalMousePos()
{
	FVector2D mousePos;
	FVector2D viewportSize;
	UGameViewportClient* viewport = GEngine->GameViewport;

	check(viewport);

	viewport->GetViewportSize(viewportSize);

	if (viewport->IsFocused(viewport->Viewport) && viewport->GetMousePosition(mousePos)) 
	{
		this->mouseOriginalPos = mousePos;
	}
}
