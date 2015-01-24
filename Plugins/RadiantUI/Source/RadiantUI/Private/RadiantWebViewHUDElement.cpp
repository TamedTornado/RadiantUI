// Copyright 2014 Joseph Riedel, Inc. All Rights Reserved.
// See LICENSE for licensing terms.

#include "RadiantUIPrivatePCH.h"
#include "JSCall.h"

#if PLATFORM_WINDOWS
#include <windows.h>
#endif

#include "Json.h"
#include "StringConv.h"
#include "CanvasItem.h"
#include "InputEvents.h"
// 
// #if PLATFORM_WINDOWS
// 
// inline int ExtendedKeyBits(int VK)
// {
// 	if ((VK == VK_LSHIFT) || (VK == VK_RSHIFT)
// 		|| (VK == VK_LCONTROL) || (VK == VK_RCONTROL)
// 		|| (VK == VK_LMENU) || (VK == VK_RMENU)
// 		|| (VK == VK_LWIN) || (VK == VK_RWIN))
// 	{
// 		return (1 << 24);
// 	}
// 
// 	return 0;
// }
// 
// #define MAP_VKEY(__FKEY, __VK) if (Key == EKeys::__FKEY) { return __VK; }
// 
// int GetVirtualKeyCode(const FKey& Key)
// {
// 	MAP_VKEY(BackSpace, VK_BACK);
// 	MAP_VKEY(Tab, VK_TAB);
// 	MAP_VKEY(Enter, VK_RETURN);
// 	MAP_VKEY(Pause, VK_PAUSE);
// 	MAP_VKEY(CapsLock, VK_CAPITAL);
// 	MAP_VKEY(Escape, VK_ESCAPE);
// 	MAP_VKEY(PageUp, VK_PRIOR);
// 	MAP_VKEY(PageDown, VK_NEXT);
// 	MAP_VKEY(End, VK_END);
// 	MAP_VKEY(Home, VK_HOME);
// 	MAP_VKEY(Left, VK_LEFT);
// 	MAP_VKEY(Up, VK_UP);
// 	MAP_VKEY(Right, VK_RIGHT);
// 	MAP_VKEY(Down, VK_DOWN);
// 	MAP_VKEY(Insert, VK_INSERT);
// 	MAP_VKEY(Delete, VK_DELETE);
// 	MAP_VKEY(NumPadZero, VK_NUMPAD0);
// 	MAP_VKEY(NumPadOne, VK_NUMPAD1);
// 	MAP_VKEY(NumPadTwo, VK_NUMPAD2);
// 	MAP_VKEY(NumPadThree, VK_NUMPAD3);
// 	MAP_VKEY(NumPadFour, VK_NUMPAD4);
// 	MAP_VKEY(NumPadFive, VK_NUMPAD5);
// 	MAP_VKEY(NumPadSix, VK_NUMPAD6);
// 	MAP_VKEY(NumPadSeven, VK_NUMPAD7);
// 	MAP_VKEY(NumPadEight, VK_NUMPAD8);
// 	MAP_VKEY(NumPadNine, VK_NUMPAD9);
// 	MAP_VKEY(Multiply, VK_MULTIPLY);
// 	MAP_VKEY(Add, VK_ADD);
// 	MAP_VKEY(Subtract, VK_SUBTRACT);
// 	MAP_VKEY(Decimal, VK_DECIMAL);
// 	MAP_VKEY(Divide, VK_DIVIDE);
// 	MAP_VKEY(F1, VK_F1);
// 	MAP_VKEY(F2, VK_F2);
// 	MAP_VKEY(F3, VK_F3);
// 	MAP_VKEY(F4, VK_F4);
// 	MAP_VKEY(F5, VK_F5);
// 	MAP_VKEY(F6, VK_F6);
// 	MAP_VKEY(F7, VK_F7);
// 	MAP_VKEY(F8, VK_F8);
// 	MAP_VKEY(F9, VK_F9);
// 	MAP_VKEY(F10, VK_F10);
// 	MAP_VKEY(F11, VK_F11);
// 	MAP_VKEY(F12, VK_F12);
// 	MAP_VKEY(NumLock, VK_NUMLOCK);
// 	MAP_VKEY(LeftShift, VK_LSHIFT);
// 	MAP_VKEY(RightShift, VK_LSHIFT);
// 	MAP_VKEY(LeftControl, VK_LSHIFT);
// 	MAP_VKEY(RightControl, VK_LSHIFT);
// 	MAP_VKEY(LeftAlt, VK_LSHIFT);
// 	MAP_VKEY(RightAlt, VK_LSHIFT);
// 	MAP_VKEY(SpaceBar, VK_SPACE);
// 	MAP_VKEY(Zero, 0x30);
// 	MAP_VKEY(One, 0x31);
// 	MAP_VKEY(Two, 0x32);
// 	MAP_VKEY(Three, 0x33);
// 	MAP_VKEY(Four, 0x34);
// 	MAP_VKEY(Five, 0x35);
// 	MAP_VKEY(Six, 0x36);
// 	MAP_VKEY(Seven, 0x37);
// 	MAP_VKEY(Eight, 0x38);
// 	MAP_VKEY(Nine, 0x39);
// 	MAP_VKEY(A, 0x41)
// 	MAP_VKEY(B, 0x42)
// 	MAP_VKEY(C, 0x43)
// 	MAP_VKEY(D, 0x44)
// 	MAP_VKEY(E, 0x45)
// 	MAP_VKEY(F, 0x46)
// 	MAP_VKEY(G, 0x47)
// 	MAP_VKEY(H, 0x48)
// 	MAP_VKEY(I, 0x49)
// 	MAP_VKEY(J, 0x4A)
// 	MAP_VKEY(K, 0x4B)
// 	MAP_VKEY(L, 0x4C)
// 	MAP_VKEY(M, 0x4D)
// 	MAP_VKEY(N, 0x4E)
// 	MAP_VKEY(O, 0x4F)
// 	MAP_VKEY(P, 0x50)
// 	MAP_VKEY(Q, 0x51)
// 	MAP_VKEY(R, 0x52)
// 	MAP_VKEY(S, 0x53)
// 	MAP_VKEY(T, 0x54)
// 	MAP_VKEY(U, 0x55)
// 	MAP_VKEY(V, 0x56)
// 	MAP_VKEY(W, 0x57)
// 	MAP_VKEY(X, 0x58)
// 	MAP_VKEY(Y, 0x59)
// 	MAP_VKEY(Z, 0x5A)
// 	MAP_VKEY(Semicolon, VK_OEM_1);
// 	MAP_VKEY(Equals, VK_OEM_PLUS);
// 	MAP_VKEY(Comma, VK_OEM_COMMA);
// 	MAP_VKEY(Underscore, VK_OEM_MINUS);
// 	MAP_VKEY(Period, VK_OEM_PERIOD);
// 	MAP_VKEY(Slash, VK_OEM_2);
// 	MAP_VKEY(Tilde, VK_OEM_3);
// 	MAP_VKEY(LeftBracket, VK_OEM_4);
// 	MAP_VKEY(Backslash, VK_OEM_5);
// 	MAP_VKEY(RightBracket, VK_OEM_6);
// 	MAP_VKEY(Quote, VK_OEM_7);
// 	return 0;
// }
// 
// int GetCurrentModifiers(const FInputEvent& KeyEvent, const FKey& Key)
// {
// 	int Modifiers = 0;
// 
// 	if (KeyEvent.IsAltDown())
// 	{
// 		Modifiers |= CEFRT_AltDown;
// 	}
// 
// 	if (KeyEvent.IsControlDown())
// 	{
// 		Modifiers |= CEFRT_ControlDown;
// 	}
// 
// 	if (KeyEvent.IsShiftDown())
// 	{
// 		Modifiers |= CEFRT_ShiftDown;
// 	}
// 
// 	if ((Key == EKeys::LeftShift) ||
// 		(Key == EKeys::LeftAlt) ||
// 		(Key == EKeys::LeftControl))
// 	{
// 		Modifiers |= CEFRT_IsLeft;
// 	}
// 
// 	if ((Key == EKeys::RightShift) ||
// 		(Key == EKeys::LeftAlt) ||
// 		(Key == EKeys::LeftControl))
// 	{
// 		Modifiers |= CEFRT_IsLeft;
// 	}
// 
// 	if ((Key == EKeys::NumPadZero) ||
// 		(Key == EKeys::NumPadOne) ||
// 		(Key == EKeys::NumPadTwo) ||
// 		(Key == EKeys::NumPadThree) ||
// 		(Key == EKeys::NumPadFour) ||
// 		(Key == EKeys::NumPadFive) ||
// 		(Key == EKeys::NumPadSix) ||
// 		(Key == EKeys::NumPadSeven) ||
// 		(Key == EKeys::NumPadEight) ||
// 		(Key == EKeys::NumPadNine) ||
// 		(Key == EKeys::Multiply) ||
// 		(Key == EKeys::Add) ||
// 		(Key == EKeys::Subtract) ||
// 		(Key == EKeys::Decimal) ||
// 		(Key == EKeys::Divide))
// 	{
// 		Modifiers |= CEFRT_IsKeyPad;
// 	}
// 
// 	if (::GetKeyState(VK_NUMLOCK) & 1)
// 	{
// 		Modifiers |= CEFRT_NumLockOn;
// 	}
// 
// 	if (::GetKeyState(VK_CAPITAL) & 1)
// 	{
// 		Modifiers |= CEFRT_CapsLockOn;
// 	}
// 
// 	return Modifiers;
// }
// 
// #endif
// }

#define REPLY_IF_NOT_READY(...) if (!HUDElement.IsValid() || !HUDOwner.IsValid() || !HUDElement->WebView.IsValid() || !HUDElement->WebView->GetBrowser()) return __VA_ARGS__
#define HITTEST(...)
//#define HITTEST(...) if (!SWidget::UseLegacyHittest() && !FSlateApplication::Get().GetMouseCaptor().IsValid() && !const_cast<SRadiantWebViewHUDElement*>(this)->OnHitTest(MyGeometry, MouseEvent.GetScreenSpacePosition())) return __VA_ARGS__


// Dead code still here until I can convert it.

// 
// void DispatchSlateKey(ICefWebView* WebView, const FKeyEvent& KeyEvent, bool Pressed)
// {
// 	CefRuntimeKeyEvent Event;
// 	FMemory::MemZero(Event);
// 	Event.Type = Pressed ? CEFRT_RawKeyDown : CEFRT_KeyUp;
// 
// 	const FKey Key = KeyEvent.GetKey();
// 
// 	int VirtualKey = GetVirtualKeyCode(Key);
// 	int ScanCode = MapVirtualKey(VirtualKey, MAPVK_VK_TO_VSC);
// 	Event.WindowsKeyCode = VirtualKey;
// 	Event.NativeKeyCode = (ScanCode << 16) | ExtendedKeyBits(VirtualKey);
// 	Event.NativeKeyCode |= Pressed ? 0 : (1 << 30);
// 	Event.Modifiers = GetCurrentModifiers(KeyEvent, Key);
// 	WebView->SendKeyEvent(Event);
// }
// 
// void DispatchSlateChar(ICefWebView* WebView, const FCharacterEvent& KeyEvent)
// {
// 	CefRuntimeKeyEvent Event;
// 	FMemory::MemZero(Event);
// 	Event.Type = CEFRT_Char;
// 
// 	/*
// 	const FKey Key = KeyEvent.GetKey();
// 
// 	int VirtualKey = GetVirtualKeyCode(Key);
// 	int ScanCode = MapVirtualKey(VirtualKey, MAPVK_VK_TO_VSC);
// 	if (ScanCode == 0)
// 	{
// 		return;
// 	}
// 	Event.NativeKeyCode = (ScanCode << 16) | ExtendedKeyBits(__VK);
// 	*/
// 
// 	Event.WindowsKeyCode = KeyEvent.GetCharacter();
// 	Event.Modifiers = GetCurrentModifiers(KeyEvent, EKeys::Invalid);
// 	WebView->SendKeyEvent(Event);
// }

// FCursorReply SRadiantWebViewHUDElement::OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const
// {
// 	REPLY_IF_NOT_READY(FCursorReply::Unhandled());
// 	HITTEST(FCursorReply::Unhandled());
// 
// 	if (HUDElement->WebView->GetMouseCursor() == ERadiantWebViewCursor::Hover)
// 	{
// 		return FCursorReply::Cursor(EMouseCursor::Hand);
// 	}
// 
// 	return FCursorReply::Cursor(EMouseCursor::Default);
// }
// 
// FReply SRadiantWebViewHUDElement::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyboardEvent)
// {
// 	REPLY_IF_NOT_READY(FReply::Unhandled());
// 	if (HUDElement->InputMode != ERadiantHUDElementInputMode::MouseAndKeyboard)
// 	{
// 		return FReply::Unhandled();
// 	}
// 	DispatchSlateKey(HUDElement->WebView->GetBrowser(), InKeyboardEvent, true);
// 	return FReply::Handled();
// }
// 
// FReply SRadiantWebViewHUDElement::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyboardEvent)
// {
// 	REPLY_IF_NOT_READY(FReply::Unhandled());
// 	if (HUDElement->InputMode != ERadiantHUDElementInputMode::MouseAndKeyboard)
// 	{
// 		return FReply::Unhandled();
// 	}
// 	DispatchSlateKey(HUDElement->WebView->GetBrowser(), InKeyboardEvent, false);
// 	return SCompoundWidget::OnKeyUp(MyGeometry, InKeyboardEvent);
// }
// 
// FReply SRadiantWebViewHUDElement::OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent)
// {
// 	REPLY_IF_NOT_READY(FReply::Unhandled());
// 	if (HUDElement->InputMode != ERadiantHUDElementInputMode::MouseAndKeyboard)
// 	{
// 		return FReply::Unhandled();
// 	}
// 	DispatchSlateChar(HUDElement->WebView->GetBrowser(), InCharacterEvent);
// 	return SCompoundWidget::OnKeyChar(MyGeometry, InCharacterEvent);
// }
// 
// bool SRadiantWebViewHUDElement::SupportsKeyboardFocus() const
// {
// 	return true;
// }
// 
// FReply SRadiantWebViewHUDElement::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
// {
// 	REPLY_IF_NOT_READY(FReply::Handled());
// 	HUDElement->WebView->GetBrowser()->SendFocusEvent(true);
// 	return FReply::Handled();
// }
// 
// void SRadiantWebViewHUDElement::OnFocusLost(const FFocusEvent& InFocusEvent)
// {
// 	REPLY_IF_NOT_READY();
// 	HUDElement->WebView->GetBrowser()->SendFocusEvent(false);
// }

URadiantWebViewHUDElement::URadiantWebViewHUDElement(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bVisible = true;

	Position = FVector2D::ZeroVector;
	Size = FVector2D(1, 1);
	bAutoMatchViewportResolution = true;
	ViewportResolutionFactor = FVector2D(1, 1);
	bMouseThumbNavigate = false;

	InputMode = ERadiantHUDElementInputMode::MouseOnly;
	HitTest = ERadiantHUDElementHitTest::Alpha;
	DefaultSettings.RefreshRate = 0.0f;
	DefaultSettings.bTransparentRendering = true;
	DefaultSettings.bProjectedCursor = false;
	World = nullptr;

}

void URadiantWebViewHUDElement::PostInitProperties()
{
	Super::PostInitProperties();

	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		WebView = MakeShareable(new FRadiantWebView(DefaultSettings));
		WebView->OnExecuteJSHook.AddUObject(this, &URadiantWebViewHUDElement::OnExecuteJSHook);
	}
}

UWorld* URadiantWebViewHUDElement::GetWorld() const
{
	return World;
}

void URadiantWebViewHUDElement::SetVisible(bool IsVisible)
{
	bVisible = IsVisible;
//	SetSlateVisibility();
}

void URadiantWebViewHUDElement::SetHitTest(TEnumAsByte<ERadiantHUDElementHitTest::Type> InHitTest)
{
	HitTest = InHitTest;
//	SetSlateVisibility();
}

void URadiantWebViewHUDElement::SetInputMode(TEnumAsByte<ERadiantHUDElementInputMode::Type> InInputMode)
{
	InputMode = InInputMode;
//	SetSlateVisibility();
}

bool URadiantWebViewHUDElement::CanNavigateForward()
{
	check(WebView.IsValid());
	return WebView->CanNavigateForward();
}

bool URadiantWebViewHUDElement::CanNavigateBackward()
{
	check(WebView.IsValid()); 
	return WebView->CanNavigateBackward();
}

void URadiantWebViewHUDElement::NavigateForward()
{
	check(WebView.IsValid());
	WebView->NavigateForward();
}

void URadiantWebViewHUDElement::NavigateBackward()
{
	check(WebView.IsValid());
	WebView->NavigateBackward();
}

void URadiantWebViewHUDElement::LoadURL(const FString& InURL)
{
	check(WebView.IsValid());
	WebView->LoadURL(InURL);
}

FString URadiantWebViewHUDElement::GetURL()
{
	check(WebView.IsValid());
	return WebView->GetURL();
}

void URadiantWebViewHUDElement::SetRefreshRate(float InFramesPerSecond)
{
	check(WebView.IsValid());
	WebView->SetRefreshRate(InFramesPerSecond);
}

float URadiantWebViewHUDElement::GetRefreshRate()
{
	check(WebView.IsValid());
	return WebView->GetRefreshRate();
}

void URadiantWebViewHUDElement::CallJavaScriptFunction(std::string HookName, std::string stringData)
{
	if (!HookName.empty() && !stringData.empty() && WebView.IsValid())
	{
		ICefRuntimeVariantList* List = WebView->GetVariantFactory()->CreateList(0);

//		FTCHARToUTF8 Convert(*stringData);
		ICefRuntimeVariant* Variant = WebView->GetVariantFactory()->CreateString(stringData.c_str());//Convert.Get());

		if (Variant)
		{
			List->SetValue(List->GetSize(), Variant);
		}

		if (List->GetSize() < 1)
		{
			List->Release();
			List = nullptr;

			UE_LOG(RadiantUILog, Error, TEXT("Failed to make a argument list for the function"));
			return;
		}
		//FTCHARToUTF8 HookNameConvert(*HookName);

		WebView->CallJavaScriptFunction(HookName.c_str(), List);

		if (List)
		{
			List->Release();
		}
	}
}

void URadiantWebViewHUDElement::CallJavaScriptFunction(const FString &HookName, UObject* Parameters)
{
	if (!HookName.IsEmpty() && Parameters && WebView.IsValid())
	{
		ICefRuntimeVariantList* Arguments = FJavaScriptHelper::CreateVariantList(Parameters->GetClass(), Parameters, WebView->GetVariantFactory());
		FTCHARToUTF8 Convert(*HookName);
		WebView->CallJavaScriptFunction(Convert.Get(), Arguments);
		if (Arguments)
		{
			Arguments->Release();
		}
	}
}

void URadiantWebViewHUDElement::OnExecuteJSHook(const FString& HookName, ICefRuntimeVariantList* Arguments)
{
	// Use the Radiant way, looking for blueprints deriving from the HUD element.
	FJavaScriptHelper::ExecuteHook(this, HookName, Arguments);

	FTCHARToUTF8 HookNameConvert(*HookName);

	// Use the C++ way, calling any interested listeners.
	HandleJSONFunctions(HookNameConvert.Get(), Arguments);
}

bool URadiantWebViewHUDElement::HandleJSONFunctions(std::string HookName, ICefRuntimeVariantList* Arguments)
{
	if (JSONFunctions.find(HookName) != JSONFunctions.end())
	{
		auto func = JSONFunctions[HookName];

		// Get the first argument, hopefully it's a string.

		if (Arguments->GetSize() == 0)
		{
			// If there's no arguments, just send it with a nullptr.
			func(nullptr);
			return true;
		} else if (Arguments->GetSize() == 1)
		{
			auto arg0 = Arguments->GetValue(0);

			if (arg0->IsString())
			{
				ICefRuntimeVariantString *argStr = static_cast<ICefRuntimeVariantString *>(arg0);

				FString jsonStr = FString(argStr->GetValue());

				// Let's parse it and pass a FJsonObject
				
				const TSharedRef<TJsonReader<TCHAR>> jsonReader = FJsonStringReader::Create(jsonStr);

				TSharedPtr<FJsonObject> dataObj = MakeShareable(new FJsonObject());

				if (FJsonSerializer::Deserialize(jsonReader, dataObj))
				{
					func(dataObj);
				} else
				{
					UE_LOG(RadiantUILog, Error, TEXT("Function hook %s, incoming argument failed to parse as JSON: %s"), UTF8_TO_TCHAR(HookName.c_str()), *jsonStr);
					return false;
				}

				return true;
			} else
			{
				UE_LOG(RadiantUILog, Error, TEXT("Function hook %s, incoming argument is not a string."), UTF8_TO_TCHAR(HookName.c_str()));
			}
		} else
		{
			UE_LOG(RadiantUILog, Error, TEXT("Function hook %s, argument count not 0 or 1 (it's %d)"), UTF8_TO_TCHAR(HookName.c_str()), Arguments->GetSize());
		}

	}

	return false;
}

void URadiantWebViewHUDElement::BindJSONFunction(std::string hookName, std::function<void(TSharedPtr<FJsonObject>)> boundFunction)
{
	if (JSONFunctions.find(hookName) != JSONFunctions.end())
	{
		UE_LOG(RadiantUILog, Warning, TEXT("Function hook %s is already bound, rebinding to new function"), UTF8_TO_TCHAR(hookName.c_str()));
	}

	JSONFunctions[hookName] = boundFunction;
}


void URadiantWebViewHUDElement::UnbindJSONFunction(std::string hookName)
{
	if (JSONFunctions.find(hookName) != JSONFunctions.end())
	{
		JSONFunctions.erase(hookName);
	}
}

void URadiantWebViewHUDElement::RemoveAllJSONBindings()
{
	JSONFunctions.clear();
}

TScriptInterface<IRadiantJavaScriptFunctionCallTargetInterface> URadiantWebViewHUDElement::GetJavaScriptCallContext()
{
	return TScriptInterface<IRadiantJavaScriptFunctionCallTargetInterface>(this);
}

void URadiantWebViewHUDElement::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	static const int ArchiveVersion = 1;

	int Version = ArchiveVersion;

	Ar << Version;
}

void URadiantWebViewHUDElement::DrawHUD(UCanvas* Canvas, const FVector2D ViewportSize)
{
	ItemPosition = ViewportSize * Position;
	ItemSize = ViewportSize * Size;

	ItemPosition.X = FMath::FloorToFloat(ItemPosition.X + 0.5f);
	ItemPosition.Y = FMath::FloorToFloat(ItemPosition.Y + 0.5f);
	ItemSize.X = FMath::FloorToFloat(ItemSize.X + 0.5f);
	ItemSize.Y = FMath::FloorToFloat(ItemSize.Y + 0.5f);


	if (bAutoMatchViewportResolution)
	{
		WebView->Resize(FIntPoint(FMath::FloorToInt((ItemSize.X*ViewportResolutionFactor.X) + 0.5f), FMath::FloorToInt((ItemSize.Y*ViewportResolutionFactor.Y) + 0.5f)));
	}

	
	if (WebView->WebViewTexture && WebView->WebViewTexture->Resource)
	{
		auto texture = WebView->WebViewTexture;

		FCanvasTileItem TileItem(ItemPosition, texture->Resource, ItemSize, FLinearColor::White);
		TileItem.BlendMode = WebView->IsTransparentRendering() ? SE_BLEND_Translucent : SE_BLEND_Opaque;
		Canvas->DrawItem(TileItem);

	}

}


FIntPoint URadiantWebViewHUDElement::LocalToTexture(FVector2D local)
{
	check(local.X>0 && local.Y>0);

	FIntPoint textureSize = WebView->GetSize();

	FVector2D scale = FVector2D(textureSize.X / ItemSize.X, textureSize.Y / ItemSize.Y);

	return FIntPoint(local.X*scale.X, local.Y*scale.Y);
}

bool URadiantWebViewHUDElement::OnHitTest(FVector2D CursorPosition)
{
	if (!bVisible)
	{
		return false;
	}

	if (HitTest == ERadiantHUDElementHitTest::None)
	{
		return false;
	}

	FVector2D localPosition = CursorPosition-ItemPosition;
	// Basic bounds check

	if (localPosition.X<0 || localPosition.X>ItemSize.X ||
		localPosition.Y<0 || localPosition.Y>ItemSize.Y)
	{
		return false;
	}

	if (HitTest == ERadiantHUDElementHitTest::Alpha)
	{
		FIntPoint texturePos = LocalToTexture(localPosition);

		return (WebView.IsValid()) ? (WebView->GetPixelAlpha(texturePos.X, texturePos.Y) > 0) : false;
	}

	return true;

}

void URadiantWebViewHUDElement::HandleMouseMove(FRadiantPointerEvent &event)
{
	if (InputMode == ERadiantHUDElementInputMode::NoInput)
	{
		return;
	}

	FVector2D localPos = event.GetScreenSpacePosition() - ItemPosition;
	FIntPoint texturePos = LocalToTexture(localPos);

	CefRuntimeMouseEvent Event;
	Event.X = texturePos.X;
	Event.Y = texturePos.Y;
	Event.Modifiers = event.GetCEFModifiers();

	WebView->GetBrowser()->SendMouseMoveEvent(Event, false);
}

void URadiantWebViewHUDElement::HandleMouseButtonDown(FRadiantPointerEvent &event)
{
	if (InputMode == ERadiantHUDElementInputMode::NoInput)
	{
		return;
	}

	FVector2D localPos = event.GetScreenSpacePosition() - ItemPosition;
	FIntPoint texturePos = LocalToTexture(localPos);

	CefRuntimeMouseEvent Event;
	Event.X = texturePos.X;
	Event.Y = texturePos.Y;
	Event.Modifiers = event.GetCEFModifiers();

	WebView->GetBrowser()->SendMouseClickEvent(Event, event.GetCEFMouseButton(), false, 1);

}

void URadiantWebViewHUDElement::HandleMouseButtonUp(FRadiantPointerEvent &event)
{
	if (InputMode == ERadiantHUDElementInputMode::NoInput)
	{
		return;
	}

	FVector2D localPos = event.GetScreenSpacePosition() - ItemPosition;
	FIntPoint texturePos = LocalToTexture(localPos);

	CefRuntimeMouseEvent Event;
	Event.X = texturePos.X;
	Event.Y = texturePos.Y;
	Event.Modifiers = event.GetCEFModifiers();

	WebView->GetBrowser()->SendMouseClickEvent(Event, event.GetCEFMouseButton(), true, 1);
}

void URadiantWebViewHUDElement::HandleMouseWheel(FRadiantPointerEvent &event)
{
	if (InputMode == ERadiantHUDElementInputMode::NoInput)
	{
		return;
	}

	FVector2D localPos = event.GetScreenSpacePosition() - ItemPosition;
	FIntPoint texturePos = LocalToTexture(localPos);

	CefRuntimeMouseEvent Event;
	Event.X = texturePos.X;
	Event.Y = texturePos.Y;
	Event.Modifiers = event.GetCEFModifiers();

	WebView->GetBrowser()->SendMouseWheelEvent(Event, 0, FMath::FloorToInt(event.GetWheelDelta()*80.f + 05.f));

}

void URadiantWebViewHUDElement::HandleMouseDoubleClick(FRadiantPointerEvent &event)
{
	if (InputMode == ERadiantHUDElementInputMode::NoInput)
	{
		return;
	}

	FVector2D localPos = event.GetScreenSpacePosition() - ItemPosition;
	FIntPoint texturePos = LocalToTexture(localPos);

	CefRuntimeMouseEvent Event;
	Event.X = texturePos.X;
	Event.Y = texturePos.Y;
	Event.Modifiers = event.GetCEFModifiers();

	WebView->GetBrowser()->SendMouseClickEvent(Event, event.GetCEFMouseButton(), false, 2);

}

