// Fill out your copyright notice in the Description page of Project Settings.

#include "MainUI.h"
#include <ChatBrowser.h>
#include <HomeBrowser.h>

void UMainUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ChatButton) {
		ChatButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleChatButtonClick);
	}

	if (HomeButton) {
		HomeButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleHomeButtonClick);
	}

	if (SaveButton) {
		SaveButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleSaveButtonClick);
	}

	if (StoreButton) {
		StoreButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleStoreButtonClick);
	}

	if (AccountButton) {
		AccountButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleAccountButtonClick);
	}

	if (NotificationButton) {
		NotificationButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleNotificationButtonClick);
	}

	if (PublishButton) {
		PublishButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handlePublishButtonClick);
	}

	if (OrderButton) {
		OrderButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleOrderButtonClick);
	}

	if (ProjectHistoryButton) {
		ProjectHistoryButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleProjectHistoryButtonClick);
	}

	if (OrderSummaryButton) {
		OrderSummaryButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleOrderSummaryButtonClick);
	}

	if (ObjectButton) {
		ObjectButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleObjectButtonClick);
	}

	if (MEPButton) {
		MEPButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleMEPButtonClick);
	}

	if (MaterialButton) {
		MaterialButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleMaterialButtonClick);
	}

	if (QeraButton) {
		QeraButton->OnClicked.AddUniqueDynamic(this, &UMainUI::handleQeraButtonClick);
	}

	_browsers = { ChatBrowser, HomeBrowser, StoreBrowser, AccountBrowser, NotificationBrowser,
	PublishBrowser, OrderBrowser, ProjectHistoryBrowser, OrderSummaryBrowser, ObjectBrowser,
	MEPBrowser, MaterialBrowser, QeraBrowser };

}

void UMainUI::_toggleBrowser(UBrowserWidget* Browser, const FString& URL)
{
	auto isVisible {Browser->IsVisible()};
	for (UBrowserWidget* browser : _browsers)
	{
		if (browser->IsVisible()) {
			browser->LoadURL(TEXT("about:blank"));
			browser->HideBrowser();
		}
	}

	if (isVisible) return;

	if (!Browser->IsVisible()) {
		Browser->LoadURL(URL);
		Browser->ShowBrowser();
	}
}

void UMainUI::handleSaveButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Save %s"), *TokenBox->GetText().ToString());
	OnAccessToken.ExecuteIfBound(*TokenBox->GetText().ToString());

	for (UBrowserWidget* browser : _browsers)
	{
		if (IsValid(browser))
		{
			browser->HandleOnAccessToken(*TokenBox->GetText().ToString());
		}
	}
}

void UMainUI::handleChatButtonClick()
{
	_toggleBrowser(ChatBrowser, TEXT("https://stage-chat.zurutech.online/"));
}

void UMainUI::handleHomeButtonClick()
{
	_toggleBrowser(HomeBrowser, TEXT("https://stage-home.zurutech.online/?version=504&platform=editor&dcversion=v0.0.1"));
}

void UMainUI::handleStoreButtonClick()
{
	_toggleBrowser(StoreBrowser, TEXT("https://stage-website-2024.zurutech.online/store"));
}

void UMainUI::handleAccountButtonClick()
{
	_toggleBrowser(AccountBrowser, TEXT("https://stage-accounts.zurutech.online/"));
}

void UMainUI::handleNotificationButtonClick()
{
	_toggleBrowser(NotificationBrowser, TEXT("https://stage-notification.zurutech.online/"));
}

void UMainUI::handlePublishButtonClick()
{
	_toggleBrowser(PublishBrowser, TEXT("https://stage-home.zurutech.online/publish/404"));
}

void UMainUI::handleOrderButtonClick()
{
	_toggleBrowser(OrderBrowser, TEXT("https://stage-home.zurutech.online/my-orders"));
}

void UMainUI::handleProjectHistoryButtonClick()
{
	_toggleBrowser(ProjectHistoryBrowser, TEXT("https://stage-home.zurutech.online/version-history/404"));
}

void UMainUI::handleOrderSummaryButtonClick()
{
	_toggleBrowser(OrderSummaryBrowser, TEXT("https://stage-home.zurutech.online/cart/404"));
}

void UMainUI::handleObjectButtonClick()
{
	_toggleBrowser(ObjectBrowser, TEXT("https://assets-v2.zurutech.online/#/object-library"));
}

void UMainUI::handleMEPButtonClick()
{
	_toggleBrowser(MEPBrowser, TEXT("https://assets-v2.zurutech.online/#/fixture-library"));
}

void UMainUI::handleMaterialButtonClick()
{
	_toggleBrowser(MaterialBrowser, TEXT("https://assets-v2.zurutech.online/#/material-library"));
}

void UMainUI::handleQeraButtonClick()
{
	_toggleBrowser(QeraBrowser, TEXT("https://stage-home.zurutech.online/qera/"));
}