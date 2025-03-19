// Copyright (c) 2014-2025 Zuru Tech HK Limited, All rights reserved.

#pragma once

#include "Components/Widget.h"
#include "CoreMinimal.h"

#include "SWebBrowser.h"

#include "DCWebBrowser.generated.h"
UENUM()
enum class EFileDialogType : uint8
{
	MultipleFiles,
	SingleFile,
};


UCLASS()
class CEF_DEMO_API UDCWebBrowser : public UWidget {
	GENERATED_UCLASS_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUrlChanged, const FText&, Text);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPageLoaded);

	/**
	 * Load the specified URL
	 *
	 * \param newURL New URL to load
	 */
	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	void LoadURL(const FString& newURL);

	/** Called when the Url changes. */
	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnUrlChanged OnUrlChanged{};

	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnPageLoaded OnPageLoaded;

	/**
	 * \brief Focuses the web browser display widget
	 **/
	void SetFocus() const;

	TSharedPtr<SWebBrowser> GetSlateBrowser();

	void ReleaseSlateResources(bool bReleaseChildren) override;


	// Set multiple or single file dialog selection.
	void SetFileDialogType(EFileDialogType type);

#if WITH_EDITOR
	const FText GetPaletteCategory() override;
#endif

	/** URL that the browser will initially navigate to. The URL should include the protocol, eg http:// */
	UPROPERTY(EditAnywhere, Category = Appearance)
	FString InitialURL{ "about:blank" };

	/** Use custom Unreal DPI scaling, otherwise use OS DPI scaling */
	UPROPERTY(EditAnywhere, Category = Appearance)
	bool bUseApplicationDPI{ true };

	/** Should the browser window support transparency. */
	UPROPERTY(EditAnywhere, Category = Appearance)
	bool bSupportsTransparency{ true };

	// UWidget interface
	TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

private:
	TSharedPtr<SWebBrowser> _webBrowserWidget{};

	EFileDialogType _fileDialogType{ EFileDialogType::SingleFile };

	void _handleOnUrlChanged(const FText& inText);

	void _onInternalPageLoaded();

	TArray<FString> _handleShowFileDialog(const FString& title, const FString& defaultPath, const TArray<FString>& fileFilters);

};
