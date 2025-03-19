// Copyright (c) 2014-2025 Zuru Tech HK Limited, All rights reserved.

#include "DCWebBrowser.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "WebBrowser"

UDCWebBrowser::UDCWebBrowser(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	bIsVariable = true;
}

void UDCWebBrowser::SetFocus() const {
	_webBrowserWidget->SetFocus();
}

void UDCWebBrowser::LoadURL(const FString& newURL) {

	if (_webBrowserWidget.IsValid()) {
		return _webBrowserWidget->LoadURL(newURL);
	}
	InitialURL = newURL;
}

void UDCWebBrowser::ReleaseSlateResources(bool bReleaseChildren) {
	Super::ReleaseSlateResources(bReleaseChildren);

	_webBrowserWidget.Reset();
}

TSharedRef<SWidget> UDCWebBrowser::RebuildWidget() {
	if (IsDesignTime()) {
		return SNew(SBox).HAlign(HAlign_Center).VAlign(VAlign_Center)[SNew(STextBlock).Text(LOCTEXT("Web Browser", "Web Browser"))];
	}
	_webBrowserWidget = SNew(SWebBrowser)
		.UseApplicationDPI(bUseApplicationDPI)
		.InitialURL(InitialURL)
		.SupportsTransparency(bSupportsTransparency)
		.ShowControls(false)
		.OnLoadCompleted(BIND_UOBJECT_DELEGATE(FSimpleDelegate, _onInternalPageLoaded))
		.OnShowFileDialog(BIND_UOBJECT_DELEGATE(FOnShowFileDialog, _handleShowFileDialog))
		.OnUrlChanged(BIND_UOBJECT_DELEGATE(FOnTextChanged, _handleOnUrlChanged));

	return _webBrowserWidget.ToSharedRef();
}

TSharedPtr<SWebBrowser> UDCWebBrowser::GetSlateBrowser() {
	return StaticCastSharedRef<SWebBrowser>(TakeWidget());
}

void UDCWebBrowser::_handleOnUrlChanged(const FText& inText) {
	OnUrlChanged.Broadcast(inText);
}

void UDCWebBrowser::_onInternalPageLoaded() {
	OnPageLoaded.Broadcast();
}

TArray<FString> UDCWebBrowser::_handleShowFileDialog(const FString& title, const FString& defaultPath, const TArray<FString>& fileFilters)
{
	return TArray<FString>();
}

#if WITH_EDITOR

void UDCWebBrowser::SetFileDialogType(EFileDialogType type)
{
	_fileDialogType = type;
}

const FText UDCWebBrowser::GetPaletteCategory() {
	return LOCTEXT("Experimental", "Experimental");
}

#endif

#undef LOCTEXT_NAMESPACE
