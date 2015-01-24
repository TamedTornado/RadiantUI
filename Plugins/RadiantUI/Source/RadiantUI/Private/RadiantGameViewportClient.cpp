// (C) 2015 Jason Maskell
#include "RadiantUIPrivatePCH.h"
#include "RadiantGameViewportClient.h"
#include "Engine.h"
#include "InputEvents.h"

bool URadiantGameViewportClient::InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples/* =1 */, bool bGamepad/* =false */)
{
	bool bResult = UGameViewportClient::InputAxis(Viewport, ControllerId, Key, Delta, DeltaTime, NumSamples,bGamepad);

	if (Key==EKeys::MouseX || Key==EKeys::MouseY)
	{
		UE_LOG(RadiantUILog, Log, TEXT("Mouse delta: %f"), Delta);
	}

	return bResult;
}

void URadiantGameViewportClient::CapturedMouseMove(FViewport* InViewport, int32 InMouseX, int32 InMouseY)
{
	UE_LOG(RadiantUILog, Log, TEXT("Captured Mouse Move: %d,%d"), InMouseX, InMouseY);
}

void URadiantGameViewportClient::MouseMove(FViewport* Viewport, int32 X, int32 Y)
{
	UE_LOG(RadiantUILog, Log, TEXT("Mouse Move: %d,%d"), X, Y);

	LastScreenSpacePosition = ScreenSpacePosition;
	ScreenSpacePosition.X = X;
	ScreenSpacePosition.Y = Y;
	Delta = ScreenSpacePosition-LastScreenSpacePosition;

	if (HUD)
	{
		TSharedPtr<FModifierKeysState> modifiers = GetModifiers();

		FRadiantPointerEvent Event = FRadiantPointerEvent(ScreenSpacePosition, LastScreenSpacePosition, PressedButtons, EKeys::LeftMouseButton, 0, *GetModifiers().Get());

		HUD->HandleMouseMove(Event);
	}
}

bool URadiantGameViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed/* =1.f */, bool bGamepad/* =false */)
{
	UE_LOG(RadiantUILog, Log, TEXT("Input Key: %s"), *Key.ToString());

	if (EventType==IE_Pressed)
	{
		PressedButtons.Add(Key);

		if (Key==EKeys::LeftMouseButton || Key==EKeys::RightMouseButton || Key==EKeys::MiddleMouseButton)
		{
			if (HUD)
			{
				TSharedPtr<FModifierKeysState> modifiers = GetModifiers();

				FRadiantPointerEvent Event = FRadiantPointerEvent(ScreenSpacePosition, LastScreenSpacePosition, PressedButtons, Key, 0, *GetModifiers().Get());

				HUD->HandleMouseButtonDown(Event);
			}
		}

	} else if (EventType==IE_Released)
	{
		PressedButtons.Remove(Key);

		if (Key == EKeys::LeftMouseButton || Key == EKeys::RightMouseButton || Key == EKeys::MiddleMouseButton)
		{
			if (HUD)
			{
				TSharedPtr<FModifierKeysState> modifiers = GetModifiers();

				FRadiantPointerEvent Event = FRadiantPointerEvent(ScreenSpacePosition, LastScreenSpacePosition, PressedButtons, Key, 0, *GetModifiers().Get());

				HUD->HandleMouseButtonUp(Event);
			}
		}

	}


	return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
}

bool URadiantGameViewportClient::InputChar(FViewport* Viewport, int32 ControllerId, TCHAR Character)
{
	UE_LOG(RadiantUILog, Log, TEXT("Input Char: %c"), Character);

	return Super::InputChar(Viewport, ControllerId, Character);
}

void URadiantGameViewportClient::SetHUD(ARadiantWebViewHUD* hud)
{
	HUD = hud;
}

TSharedPtr<FModifierKeysState> URadiantGameViewportClient::GetModifiers()
{
	TSharedPtr<FModifierKeysState> modifiers = MakeShareable<FModifierKeysState>(new FModifierKeysState(
			PressedButtons.Contains(EKeys::LeftShift),
			PressedButtons.Contains(EKeys::RightShift),
			PressedButtons.Contains(EKeys::LeftControl),
			PressedButtons.Contains(EKeys::RightControl),
			PressedButtons.Contains(EKeys::LeftAlt),
			PressedButtons.Contains(EKeys::RightAlt),
			PressedButtons.Contains(EKeys::LeftCommand),
			PressedButtons.Contains(EKeys::RightCommand),
			PressedButtons.Contains(EKeys::CapsLock)
		));

	return modifiers;
}
