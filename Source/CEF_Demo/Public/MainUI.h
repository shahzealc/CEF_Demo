// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/EditableText.h>
#include <DCWebBrowser.h>

#include "MainUI.generated.h"

DECLARE_DELEGATE_OneParam(FOnAccessToken, const FString&);


class UHomeBrowser;
class UChatBrowser;

/**
 *
 */
UCLASS()
class CEF_DEMO_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:

	FOnAccessToken OnAccessToken;

	UPROPERTY(meta = (BindWidget))
	UChatBrowser* ChatBrowser;

	UPROPERTY(meta = (BindWidget))
	UHomeBrowser* HomeBrowser;

	UPROPERTY(meta = (BindWidget))
	UButton* ChatButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton{};

	UPROPERTY(meta = (BindWidget))
	UEditableText* TokenBox{};

protected:

	void NativeOnInitialized() override;

private:

	UFUNCTION()
	void handleChatButtonClick();

	UFUNCTION()
	void handleHomeButtonClick();

	UFUNCTION()
	void handleSaveButtonClick();

};
