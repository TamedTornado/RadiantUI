// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "RadiantGameViewportClient.generated.h"

class ARadiantWebViewHUD;

/**
 * 
 */
UCLASS()
class RADIANTUI_API URadiantGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
private:
	ARadiantWebViewHUD *HUD;

public:

	bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed/* =1.f */, bool bGamepad/* =false */) override;
	bool InputChar(FViewport* Viewport,int32 ControllerId, TCHAR Character) override;

	bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples/* =1 */, bool bGamepad/* =false */) override;
	
	void CapturedMouseMove( FViewport* InViewport, int32 InMouseX, int32 InMouseY ) override;
	void MouseMove(FViewport* Viewport,int32 X,int32 Y) override;
	void SetHUD(ARadiantWebViewHUD* hud);
};
