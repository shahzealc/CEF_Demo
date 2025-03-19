// Fill out your copyright notice in the Description page of Project Settings.

#include "BrowserWidget.h"


void UBrowserWidget::NativeConstruct() {
	checkf(IsValid(_browser) || HasBoundBrowser(), TEXT("Init not called"));
	_boundBrowser = _browser->GetSlateBrowser();
	_boundBrowser->BindUObject("DCFirebase", this, true);
	_browser->OnPageLoaded.AddDynamic(this, &UBrowserWidget::_onPageLoaded);
	_isVisible = Super::IsVisible();

	Super::NativeConstruct();


	SetupBindings();
}

void UBrowserWidget::NativeDestruct() {

	// If the browser is not bound (_onEditorInitialized not called), there's no need to unregister it, since it has not been registered.
	if (HasBoundBrowser()) {
		_browser->OnPageLoaded.RemoveDynamic(this, &UBrowserWidget::_onPageLoaded);
	}
	Super::NativeDestruct();
}



FReply UBrowserWidget::NativeOnKeyDown(const FGeometry& geometry, const FKeyEvent& keyEvent) {
	return FReply::Handled();
}

TArray<FString> UBrowserWidget::GetAccessTokenObject() {

	const auto jsonObject{ MakeShared<FJsonObject>() };

	jsonObject->SetStringField("accessToken", AccessToken);

	FString result;
	const auto jsonWriter{ TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&result) };
	FJsonSerializer::Serialize(jsonObject, jsonWriter);
	jsonWriter->Close();

	return TArray{ result };
}

void UBrowserWidget::SetupBindings() {
	ExposeMethod("JS.GetAccessToken", [this](const FString&, const FString&) {
		UE_LOG(LogTemp, Log, TEXT("Calling 123 event."));

		const auto accessToken{ GetAccessTokenObject() };
		InvokeMethod("GetAccessTokenCallback", { accessToken });
		return accessToken;
		});
	_setupBindingsBrowserSpecific();
}

void UBrowserWidget::RegisterViewportResizeEvent() {

}

void UBrowserWidget::HandleOnAccessToken(const FString& accessToken)
{
	UE_LOG(LogTemp, Warning, TEXT("Got AT %s"),*accessToken);
	AccessToken = accessToken;
}

void UBrowserWidget::ExposeMethod(const FString& methodName, TFunction<TArray<FString>(const FString&, const FString&)> onMethodCalled) {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));
	_javascriptMethods.FindOrAdd(methodName) = onMethodCalled;
}

void UBrowserWidget::BindToEvent(const FString& eventName, TFunction<void(const FString&, const FString&)> eventHandler) {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));
	_eventHandlers.FindOrAdd(eventName) = eventHandler;
}

bool UBrowserWidget::HasBoundBrowser() const {
	return _boundBrowser.IsValid();
}

void UBrowserWidget::OnJavascriptCallback(const FString methodName, const bool isError, const FString& message, const FString& payload) {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));

	const auto browserName{ GetUniqueName().ToString() };

	if (_eventHandlers.Contains(methodName)) {
		UE_LOG(LogTemp, Log, TEXT("[%s] Calling event %.128s..."), *browserName, *methodName);
		_eventHandlers[methodName](message, payload);
		return;
	}

	if (_javascriptMethods.Contains(methodName)) {
		const auto methodResult = _javascriptMethods[methodName](message, payload);
		UE_LOG(
			LogTemp, Log, TEXT("[%s] JS side: method %s and returning to the browser %d results"), *browserName, *methodName, methodResult.Num());
#if WITH_EDITOR
		for (auto i = 0; i < methodResult.Num(); ++i) {
			UE_LOG(LogTemp, Log, TEXT("[%s] [%s] result %d: %.128s..."), *browserName, *methodName, i + 1, *methodResult[i]);
		}
#endif
		_boundBrowser->ExecuteJavascript(methodName);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s] Unknown js-call %s"), *browserName, *methodName);
}

FName UBrowserWidget::GetUniqueName() const {
	return _uniqueName;
}

void UBrowserWidget::HideBrowser() {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));

	if (IsVisible()) {
		UE_LOG(LogTemp, Log, TEXT("[%s] Hiding browser"), *_uniqueName.ToString());
		SetVisibility(ESlateVisibility::Collapsed);
		OnHidden.Broadcast();
	}
}

void UBrowserWidget::ShowBrowser() {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));

	if (!IsVisible()) {
		UE_LOG(LogTemp, Log, TEXT("[%s] Showing browser"), *_uniqueName.ToString());
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		OnShown.Broadcast();


	}
	if (IsValid(_browser)) {
		_browser->SetFocus();
	}
}

void UBrowserWidget::SetVisibility(ESlateVisibility InVisibility) {
	if (InVisibility == ESlateVisibility::Collapsed || InVisibility == ESlateVisibility::Hidden) {
		SetRenderScale(FVector2d(0.0, 0.0));
		_isVisible = false;
	}
	else {
		Super::SetVisibility(InVisibility);
		SetRenderScale(FVector2d(1.0, 1.0));
		_isVisible = true;
	}

	OnNativeVisibilityChanged.Broadcast(InVisibility);
	OnVisibilityChanged.Broadcast(InVisibility);
}

bool UBrowserWidget::IsVisible() const {
	return _isVisible;
}

void UBrowserWidget::SetReadyToRespond() {
	_isBrowserReady = true;
}

bool UBrowserWidget::IsReadyToRespond() const {
	return _isBrowserReady;
}

void UBrowserWidget::Reload() const {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));
	UE_LOG(LogTemp, Log, TEXT("[%s] Reloading page"), *_uniqueName.ToString());
	_boundBrowser->Reload();
}

void UBrowserWidget::LoadURL(FStringView url) const {
	LoadURL(url, {});
}

void UBrowserWidget::LoadURL(FStringView url, const TMap<FString, FString>& params) const {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));
	const FString& completeUrlToLoad = _prepareGetRequestParams(url, params);
	UE_LOG(LogTemp, Log, TEXT("[%s] Loading URL %s"), *_uniqueName.ToString(), *completeUrlToLoad);
	_boundBrowser->LoadURL(completeUrlToLoad);
}

bool UBrowserWidget::IsLoading() const {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));
	return _boundBrowser->IsLoading();
}

void UBrowserWidget::InvokeMethod(const FString& methodName, const TArray<FString>& parameters) const {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));

	const auto browserName{ GetUniqueName().ToString() };

	const auto requestFunction{ _buildFunctionCall(methodName, parameters) };
	UE_LOG(LogTemp, Log, TEXT("[%s] Invoking JS method %s"), *browserName, *requestFunction);
	_boundBrowser->ExecuteJavascript(requestFunction);
}

void UBrowserWidget::TriggerEvent(const FString& eventName, const TArray<FString>& parameters) const {
	checkf(HasBoundBrowser(), TEXT("browser is not valid"));

	const auto browserName{ GetUniqueName().ToString() };

	const auto requestFunction{ _buildFunctionCall(eventName, parameters) };
	UE_LOG(LogTemp, Log, TEXT("[%s] Triggering JS event %.128s..."), *browserName, *requestFunction);
	_boundBrowser->ExecuteJavascript(requestFunction);
}


FString UBrowserWidget::_buildFunctionCall(const FStringView methodName, const TArrayView<const FString> params) {
	FUtf8StringBuilderBase builder;
	builder.Append(methodName);
	builder.AppendChar('(');

	// Use ECMAScript 6 (ES6) template literals (`) to support multiline strings
	const auto totParams{ params.Num() };
	for (int i = 0; i < totParams; ++i) {
		builder.AppendChar('`');
		builder.Append(params[i].Replace(TEXT("`"), TEXT("\\`")));
		builder.AppendChar('`');
		if (i < totParams - 1) {
			builder.AppendChar(',');
		}
	}

	builder.Append(");");

	return builder.ToString();
}

FString UBrowserWidget::_prepareGetRequestParams(FStringView baseUrl, const TMap<FString, FString>& params) {

	FString url{ baseUrl.GetData() };
	return url;
}



