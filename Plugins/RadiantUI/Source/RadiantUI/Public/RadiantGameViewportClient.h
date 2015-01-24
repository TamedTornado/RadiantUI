// (C) 2015 Jason Maskell

#pragma once

#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "RadiantGameViewportClient.generated.h"

class ARadiantWebViewHUD;

/**
 * This GameViewPortClient implementation exists in order to allow Unreal to communicate mouse and keyboard events to HUD based Radiant UIs.

   Due to a change in UE4.5 that removed the previous functionality, this allows us to do alpha hit testing again.
 */
UCLASS()
class RADIANTUI_API URadiantGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
private:
	ARadiantWebViewHUD *HUD;

	TSet<FKey> PressedButtons;
	TSharedPtr<FModifierKeysState> GetModifiers();

	// Mouse coordinate tracking
	FVector2D ScreenSpacePosition;
	FVector2D LastScreenSpacePosition;
	FVector2D Delta;

public:

	bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed/* =1.f */, bool bGamepad/* =false */) override;
	bool InputChar(FViewport* Viewport,int32 ControllerId, TCHAR Character) override;

	bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples/* =1 */, bool bGamepad/* =false */) override;
	
	void CapturedMouseMove( FViewport* InViewport, int32 InMouseX, int32 InMouseY ) override;
	void MouseMove(FViewport* Viewport,int32 X,int32 Y) override;
	

	void SetHUD(ARadiantWebViewHUD* hud);
};
