// Copyright 2014 Joseph Riedel, Inc.All Rights Reserved.
// See LICENSE for licensing terms.

#pragma once 

#include "RadiantWebViewHUDElement.h"
#include "GameFramework/HUD.h"
#include "RadiantWebViewHUD.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RADIANTUI_API ARadiantWebViewHUD : public AHUD
{
	GENERATED_BODY()

public:

	ARadiantWebViewHUD(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Elements")
	TArray<TSubclassOf<URadiantWebViewHUDElement> > HUDElements;

	UPROPERTY(transient, BlueprintReadOnly, Category = "HUD Elements")
	TArray<URadiantWebViewHUDElement*> HUDElementInstances;

	// Begin UObject interface.
	virtual void Serialize(FArchive& Ar) override;
	// End UObject interface.

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

	// Begin AActor interface
	virtual void Tick(float InDeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;
	// End AActor Interface

	virtual void PreDrawHUD() {}
	virtual void PostDrawHUD() {}

	FVector2D GetViewportSize();

	// The RadiantGameViewportClient sends mouse events to the HUD indiscriminately, allowing it to give them to its children or not.
	void HandleMouseMove(int32 MouseX, int32 MouseY);

private:

	friend class SRadiantWebViewHUD;
};