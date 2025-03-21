// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/EditableText.h>
#include "BrowserWidget.h"
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
	UBrowserWidget* StoreBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* AccountBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* NotificationBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* PublishBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* OrderBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* ProjectHistoryBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* OrderSummaryBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* ObjectBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* MEPBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* MaterialBrowser;

	UPROPERTY(meta = (BindWidget))
	UBrowserWidget* QeraBrowser;

	// Buttons for all browsers
	UPROPERTY(meta = (BindWidget))
	UButton* ChatButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* HomeButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* StoreButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* AccountButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* NotificationButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* PublishButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* OrderButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* ProjectHistoryButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* OrderSummaryButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* ObjectButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* MEPButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* MaterialButton{};

	UPROPERTY(meta = (BindWidget))
	UButton* QeraButton{};

	UPROPERTY(meta = (BindWidget))
	UEditableText* TokenBox{};

protected:

	void NativeOnInitialized() override;

private:

	bool _isChatLoaded{};
	bool _isHomeLoaded{};

	bool _isTokenUpdated{};

	UFUNCTION()
	void handleChatButtonClick();

	UFUNCTION()
	void handleHomeButtonClick();

	UFUNCTION()
	void handleSaveButtonClick();

	UFUNCTION()
	void handleStoreButtonClick();

	UFUNCTION()
	void handleAccountButtonClick();

	UFUNCTION()
	void handleNotificationButtonClick();

	UFUNCTION()
	void handlePublishButtonClick();

	UFUNCTION()
	void handleOrderButtonClick();

	UFUNCTION()
	void handleProjectHistoryButtonClick();

	UFUNCTION()
	void handleOrderSummaryButtonClick();

	UFUNCTION()
	void handleObjectButtonClick();

	UFUNCTION()
	void handleMEPButtonClick();

	UFUNCTION()
	void handleMaterialButtonClick();

	UFUNCTION()
	void handleQeraButtonClick();
};
