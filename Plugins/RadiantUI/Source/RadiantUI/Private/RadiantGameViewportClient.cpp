// Fill out your copyright notice in the Description page of Project Settings.

#include "RadiantUIPrivatePCH.h"
#include "RadiantGameViewportClient.h"
#include "Engine.h"





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

	if (HUD)
	{
		HUD->HandleMouseMove(X, Y);
	}
}

bool URadiantGameViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed/* =1.f */, bool bGamepad/* =false */)
{
	UE_LOG(RadiantUILog, Log, TEXT("Input Key: %s"), *Key.ToString());

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
