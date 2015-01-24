// Copyright 2014 Joseph Riedel, Inc. All Rights Reserved.
// See LICENSE for licensing terms.

#pragma once 

#include "RadiantWebView.h"
#include "RadiantJavaScriptFunctionCallTargetInterface.h"
#include <functional>
#include <map>
#include "RadiantWebViewHUDElement.generated.h"

class FJsonObject;
class ARadiantWebViewHUD;
class URadiantWebViewHUDElement;
struct CefRuntimeMouseEvent;

UENUM(BlueprintType)
namespace ERadiantHUDElementInputMode
{
	enum Type
	{
		NoInput,
		MouseOnly,
		MouseAndKeyboard
	};
}

UENUM(BlueprintType)
namespace ERadiantHUDElementHitTest
{
	enum Type
	{
		None,
		Rect,
		Alpha
	};
}

struct FRadiantPointerEvent;

UCLASS(abstract, DefaultToInstanced, Blueprintable)
class RADIANTUI_API URadiantWebViewHUDElement : public UObject, public IRadiantJavaScriptFunctionCallTargetInterface
{
	GENERATED_BODY()

public:

	URadiantWebViewHUDElement(const FObjectInitializer& ObjectInitializer);

	TSharedPtr<FRadiantWebView> WebView;

	UPROPERTY(EditDefaultsOnly, Category = "WebView")
	FRadiantWebViewDefaultSettings DefaultSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD|Element")
	uint32 bVisible:1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|Element")
	uint32 bMouseThumbNavigate:1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD|Element")
	TEnumAsByte<ERadiantHUDElementInputMode::Type> InputMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD|Element")
	TEnumAsByte<ERadiantHUDElementHitTest::Type> HitTest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD|Element")
	FVector2D ViewportResolutionFactor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD|Element")
	uint32 bAutoMatchViewportResolution:1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|Element")
	FVector2D Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|Element")
	FVector2D Size;



	UFUNCTION(BlueprintCallable, Category = "HUD|Element")
	void SetVisible(bool IsVisible);

	UFUNCTION(BlueprintCallable, Category = "HUD|Element")
	void SetHitTest(TEnumAsByte<ERadiantHUDElementHitTest::Type> InHitTest);

	UFUNCTION(BlueprintCallable, Category = "HUD|Element")
	void SetInputMode(TEnumAsByte<ERadiantHUDElementInputMode::Type> InInputMode);
	
	UFUNCTION(BlueprintCallable, Category = "WebView")
	bool CanNavigateForward();

	UFUNCTION(BlueprintCallable, Category = "WebView")
	bool CanNavigateBackward();

	UFUNCTION(BlueprintCallable, Category = "WebView")
	void NavigateForward();

	UFUNCTION(BlueprintCallable, Category = "WebView")
	void NavigateBackward();

	UFUNCTION(BlueprintCallable, Category = "WebView")
	void LoadURL(const FString& URL);

	UFUNCTION(BlueprintCallable, Category = "WebView")
	FString GetURL();

	UFUNCTION(BlueprintCallable, Category = "WebView")
	void SetRefreshRate(float FramesPerSecond);

	UFUNCTION(BlueprintCallable, Category = "WebView")
	float GetRefreshRate();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = JavaScript)
	TScriptInterface<IRadiantJavaScriptFunctionCallTargetInterface> GetJavaScriptCallContext();

	virtual void CallJavaScriptFunction(const FString& HookName, UObject* Parameters) override;
	// Begin UObject Interface
	virtual void PostInitProperties() override;
	virtual void Serialize(FArchive& Ar) override;
	virtual UWorld* GetWorld() const override;
	// End UObject Interface

	void DrawHUD(UCanvas* Canvas, const FVector2D ViewportSize);

	// Return true if this element is under the current cursor position, taking into account bounds and alpha (if enabled)
	bool OnHitTest(FVector2D CursorPosition);

	void HandleMouseMove(FRadiantPointerEvent &event);
	void HandleMouseButtonDown(FRadiantPointerEvent &event);
	void HandleMouseButtonUp(FRadiantPointerEvent &event);
	void HandleMouseWheel(FRadiantPointerEvent &event);
	void HandleMouseDoubleClick(FRadiantPointerEvent &event);

	void CallJavaScriptFunction(std::string HookName, std::string stringData);
	void BindJSONFunction(std::string hookName, std::function<void(TSharedPtr<FJsonObject>)> boundFunction);
	void UnbindJSONFunction(std::string hookName);
	void RemoveAllJSONBindings();

private:
	// Changed every Draw, to show the screen position and size of this hud element.
	FVector2D ItemPosition;
	FVector2D ItemSize;

	std::map<std::string, std::function<void(TSharedPtr<FJsonObject>)>> JSONFunctions;
	bool HandleJSONFunctions(std::string HookName, ICefRuntimeVariantList* Arguments);

	UWorld* World;


	void OnExecuteJSHook(const FString& HookName, ICefRuntimeVariantList* Arguments);
	
	// Given a local coordinate, return the coordinate in the underlying texture.
	FIntPoint LocalToTexture(FVector2D local);
	friend class ARadiantWebViewHUD;
};