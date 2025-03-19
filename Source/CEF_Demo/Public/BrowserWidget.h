// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWebBrowser.h"
#include <DCWebBrowser.h>

#include "BrowserWidget.generated.h"




/**
 * \brief Delegate for the visibility change of the browser.
 * \param isVisible True if the browser is visible, false otherwise.
 */
DECLARE_MULTICAST_DELEGATE(FBrowserVisibilityChangeDelegate);

/**
 * \brief Delegate for notifying browser readiness.
 * param the name of the browser.
 */
DECLARE_DELEGATE_OneParam(FOnBrowserReady, const FName&);

/**
 * Base class for widget that contains a web browser.
 *
 * There are many methods for calling javascript events and for bind javascript events
 */
UCLASS()
class CEF_DEMO_API UBrowserWidget : public UUserWidget {
	GENERATED_BODY()

public:

	FString AccessToken{};

	void HandleOnAccessToken(const FString&);

	/**
	 * \brief Handles the showing of the browser event.
	 */
	FBrowserVisibilityChangeDelegate OnShown{};

	/**
	 * \brief Handles the hiding of the browser event.
	 */
	FBrowserVisibilityChangeDelegate OnHidden{};

	// IDCBrowserCommunicator interface
	void ExposeMethod(const FString& methodName, TFunction<TArray<FString>(const FString&, const FString&)> onMethodCalled);
	void InvokeMethod(const FString& methodName, const TArray<FString>& parameters) const;
	void TriggerEvent(const FString& eventName, const TArray<FString>& parameters) const;
	void BindToEvent(const FString& eventName, TFunction<void(const FString&, const FString&)> eventHandler);
	bool HasBoundBrowser() const;

	/**
	 * \brief Calling this function you can test the result of a registered javascript callbacks, even by blueprint.
	 * IMPORTANT: even if there are no direct Blueprint references to "OnJavascriptCallback"
	 * this method is FUNDAMENTAL for all the interactions between the web page javascript code and DC.
	 * DO NOT DELETE IT.
	 *
	 * \param methodName The name of the method/event that has been called inside CEF
	 * \param isError
	 * \param message This string will be used as the FIRST PARAMETER of the method you are calling.
	 * \param payload This string will be used as the SECOND PARAMETER of the method you are calling.
	 */
	UFUNCTION(BlueprintCallable, Category = "Dreamcatcher|Web browser")
	void OnJavascriptCallback(FString methodName, bool isError, const FString& message, const FString& payload);

	/**
	 * \brief Returns the name of the browser.
	 * \return The name of the browser.
	 */
	FName GetUniqueName() const;

	/**
	 * \brief Sets the bound browser visibility to "Collapsed".
	 */
	virtual void HideBrowser();

	/**
	 * \brief Sets the bound browser visibility to "SelfHitTestInvisible".
	 */
	virtual void ShowBrowser();

	UFUNCTION()
	void SetupBindings();

	/**
	 * \brief Reloads the bound browser current page.
	 */
	void Reload() const;

	/**
	 * \brief Load the browser with the specified URL.
	 * \param url URL of the browser.
	 */
	void LoadURL(FStringView url) const;

	/**
	 * \brief Loads the passed url with a get query made with the params in this format:
	 * "?Get_Param1=Get_Value1&Get_Param2=Get_Value2&..."
	 * \param url The starting url which the get query will be appended to and then loaded.
	 * \param params An array of strings pairs, the pairs will become Key -> GET_Param, Value -> GET_Value
	 * \return The Url with the created GET QUERY.
	 * Example:
	 * url = www.google.it;
	 * params = {{"id", "1"}, {"name","Fabre"}}  **Not the actual param format**;
	 * The loaded url will be: "www.google.it?id=1&name=Fabre"
	 */
	void LoadURL(FStringView url, const TMap<FString, FString>& params) const;

	bool IsLoading() const;

	/**
	 * \brief Attach the OnViewportResizedBPEvent to the current viewport resize dispatcher.
	 *  It is not placed in the NativeConstruct because sometimes the viewport is not ready when the event is called (causing a runtime error).
	 *  Multiple registrations cases are guarded by _isViewportResizeEventRegistered.
	 */
	UFUNCTION(BlueprintCallable, Category = "Dreamcatcher|Browser")
	void RegisterViewportResizeEvent();

	// TODO FABRE: Setting the visibility by now makes the browser no more interactive; this will change the scale as temporary fix.
	void SetVisibility(ESlateVisibility InVisibility);

	// TODO FABRE: Setting the visibility by now makes the browser no more interactive; this is a temporary fix.
	virtual bool IsVisible() const;

	void SetReadyToRespond();

	bool IsReadyToRespond() const;

protected:
	void NativeConstruct();
	void NativeDestruct();


	FReply NativeOnKeyDown(const FGeometry& geometry, const FKeyEvent& keyEvent);

	TArray<FString> GetAccessTokenObject();

	UFUNCTION()
	virtual void _onPageLoaded() {}



	UFUNCTION()
	virtual void _setupBindingsBrowserSpecific() {};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UDCWebBrowser> _browser{};

	UPROPERTY(EditDefaultsOnly, Category = "Dreamcatcher|Browser")
	FName _uniqueName{};

	FVector2D _cachedViewportSize{ FVector2D::ZeroVector };
	TSharedPtr<SWebBrowser> _boundBrowser{};

	/**
	 * \brief A map of method names and their handlers.
	 */
	TMap<FString, TFunction<TArray<FString>(const FString&, const FString&)>> _javascriptMethods;

	/**
	 * \brief A map of event names and their handlers.
	 */
	TMap<FString, TFunction<void(const FString&, const FString&)>> _eventHandlers;

	static FString _buildFunctionCall(FStringView methodName, TArrayView<const FString> params);


	/**
	 * \brief Appends to the param url the GET query format in this format:
	 * "?Get_Param1=Get_Value1&Get_Param2=Get_Value2&..."
	 * \param baseUrl The starting url which the get query will be appended to.
	 * \param params An array of strings pairs, the pairs will become Key -> Get_Param, Value -> Get_Value
	 * \return The Url with the created GET QUERY.
	 * Example:
	 * url = www.google.it;
	 * params = {{"id", "1"}, {"name","Fabre"}}
	 * return -> www.google.it?id=1&name=Fabre
	 */
	static FString _prepareGetRequestParams(FStringView baseUrl, const TMap<FString, FString>& params);

	// TODO FABRE: Setting the visibility by now makes the browser no more interactive; this is a temporary fix.
	bool _isVisible{};

	bool _isBrowserReady{};
};
