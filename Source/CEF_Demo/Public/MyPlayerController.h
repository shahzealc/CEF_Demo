// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UMainUI;

UCLASS()
class CEF_DEMO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainUI> _mainUIClass{};

	UPROPERTY()
	UMainUI* _mainUI{};

	FString _accessToken{};

	void _handleOnAccessToken(const FString&);
};
