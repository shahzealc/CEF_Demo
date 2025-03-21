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
}

void UMainUI::handleSaveButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Save %s"), *TokenBox->GetText().ToString());
	OnAccessToken.ExecuteIfBound(*TokenBox->GetText().ToString());

	TArray<UBrowserWidget*> Browsers = { ChatBrowser, HomeBrowser, StoreBrowser, AccountBrowser, NotificationBrowser,
		PublishBrowser, OrderBrowser, ProjectHistoryBrowser, OrderSummaryBrowser, ObjectBrowser,
		MEPBrowser, MaterialBrowser, QeraBrowser };

	for (UBrowserWidget* Browser : Browsers)
	{
		if (IsValid(Browser))
		{
			Browser->HandleOnAccessToken(*TokenBox->GetText().ToString());
		}
	}

	HomeBrowser->LoadURL(TEXT("https://stage-home.zurutech.online/?version=504&platform=editor&dcversion=v0.0.1"));
	ChatBrowser->LoadURL(TEXT("https://stage-chat.zurutech.online/"));
	StoreBrowser->LoadURL(TEXT("https://stage-website-2024.zurutech.online/store"));
	AccountBrowser->LoadURL(TEXT("https://stage-accounts.zurutech.online/"));
	NotificationBrowser->LoadURL(TEXT("https://stage-notification.zurutech.online/"));
	PublishBrowser->LoadURL(TEXT("https://stage-home.zurutech.online/publish/404"));
	OrderBrowser->LoadURL(TEXT("https://stage-home.zurutech.online/my-orders"));
	ProjectHistoryBrowser->LoadURL(TEXT("https://stage-home.zurutech.online/version-history/404"));
	OrderSummaryBrowser->LoadURL(TEXT("https://stage-home.zurutech.online/cart/404"));
	ObjectBrowser->LoadURL(TEXT("https://assets-v2.zurutech.online/#/object-library"));
	MEPBrowser->LoadURL(TEXT("https://assets-v2.zurutech.online/#/fixture-library"));
	MaterialBrowser->LoadURL(TEXT("https://assets-v2.zurutech.online/#/material-library"));
	QeraBrowser->LoadURL(TEXT("https://stage-home.zurutech.online/qera/"));
}

void UMainUI::handleChatButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Chat"));

	if (IsValid(ChatBrowser)) {
		ChatBrowser->IsVisible() ? ChatBrowser->HideBrowser() : ChatBrowser->ShowBrowser();
	}
}

void UMainUI::handleHomeButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Home"));

	if (IsValid(HomeBrowser)) {
		HomeBrowser->IsVisible() ? HomeBrowser->HideBrowser() : HomeBrowser->ShowBrowser();
	}
}

void UMainUI::handleStoreButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Store"));
	if (IsValid(StoreBrowser)) {
		StoreBrowser->IsVisible() ? StoreBrowser->HideBrowser() : StoreBrowser->ShowBrowser();
	}
}

void UMainUI::handleAccountButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Account"));
	if (IsValid(AccountBrowser)) {
		AccountBrowser->IsVisible() ? AccountBrowser->HideBrowser() : AccountBrowser->ShowBrowser();
	}
}

void UMainUI::handleNotificationButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Notification"));
	if (IsValid(NotificationBrowser)) {
		NotificationBrowser->IsVisible() ? NotificationBrowser->HideBrowser() : NotificationBrowser->ShowBrowser();
	}
}

void UMainUI::handlePublishButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Publish"));
	if (IsValid(PublishBrowser)) {
		PublishBrowser->IsVisible() ? PublishBrowser->HideBrowser() : PublishBrowser->ShowBrowser();
	}
}

void UMainUI::handleOrderButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Order"));
	if (IsValid(OrderBrowser)) {
		OrderBrowser->IsVisible() ? OrderBrowser->HideBrowser() : OrderBrowser->ShowBrowser();
	}
}

void UMainUI::handleProjectHistoryButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Project History"));
	if (IsValid(ProjectHistoryBrowser)) {
		ProjectHistoryBrowser->IsVisible() ? ProjectHistoryBrowser->HideBrowser() : ProjectHistoryBrowser->ShowBrowser();
	}
}

void UMainUI::handleOrderSummaryButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Order Summary"));
	if (IsValid(OrderSummaryBrowser)) {
		OrderSummaryBrowser->IsVisible() ? OrderSummaryBrowser->HideBrowser() : OrderSummaryBrowser->ShowBrowser();
	}
}

void UMainUI::handleObjectButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Object"));
	if (IsValid(ObjectBrowser)) {
		ObjectBrowser->IsVisible() ? ObjectBrowser->HideBrowser() : ObjectBrowser->ShowBrowser();
	}
}

void UMainUI::handleMEPButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("MEP"));
	if (IsValid(MEPBrowser)) {
		MEPBrowser->IsVisible() ? MEPBrowser->HideBrowser() : MEPBrowser->ShowBrowser();
	}
}

void UMainUI::handleMaterialButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Material"));
	if (IsValid(MaterialBrowser)) {
		MaterialBrowser->IsVisible() ? MaterialBrowser->HideBrowser() : MaterialBrowser->ShowBrowser();
	}
}

void UMainUI::handleQeraButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Qera"));
	if (IsValid(QeraBrowser)) {
		QeraBrowser->IsVisible() ? QeraBrowser->HideBrowser() : QeraBrowser->ShowBrowser();
	}
}
