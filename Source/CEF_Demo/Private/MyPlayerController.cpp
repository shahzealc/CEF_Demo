// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MainUI.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	_mainUI = CreateWidget<UMainUI>(this, _mainUIClass);
	_mainUI->AddToViewport();

	bShowMouseCursor = true;

	if (IsValid(_mainUI)) {
		_mainUI->OnAccessToken.BindUObject(this, &AMyPlayerController::_handleOnAccessToken);
	}

}

void AMyPlayerController::_handleOnAccessToken(const FString& accessToken)
{
	_accessToken = accessToken;
}
