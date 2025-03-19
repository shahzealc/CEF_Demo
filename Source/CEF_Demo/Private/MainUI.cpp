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

}

void UMainUI::handleChatButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Chat"));
	if (ChatBrowser) {
		ChatBrowser->LoadURL(TEXT("https://stage-chat.zurutech.online/"));
	}
}

void UMainUI::handleHomeButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Home"));

	if (HomeBrowser) {
		HomeBrowser->LoadURL(TEXT("https://stage-home.zurutech.online/?version=504&platform=editor&dcversion=v0.0.1"));
	}
}

void UMainUI::handleSaveButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Save %s"), *TokenBox->GetText().ToString());
	OnAccessToken.ExecuteIfBound(*TokenBox->GetText().ToString());
	HomeBrowser->HandleOnAccessToken(*TokenBox->GetText().ToString());
	ChatBrowser->HandleOnAccessToken(*TokenBox->GetText().ToString());
}

