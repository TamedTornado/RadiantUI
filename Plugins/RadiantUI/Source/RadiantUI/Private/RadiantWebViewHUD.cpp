// Copyright 2014 Joseph Riedel, Inc. All Rights Reserved.
// See LICENSE for licensing terms.

#include "RadiantUIPrivatePCH.h"
#include "InputEvents.h"

ARadiantWebViewHUD::ARadiantWebViewHUD(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARadiantWebViewHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	bool bUnused;
	UWorld* World = GetWorldChecked(bUnused);

	for (auto It = HUDElements.CreateConstIterator(); It; ++It)
	{
		if (*It)
		{
			URadiantWebViewHUDElement *Element = ConstructObject<URadiantWebViewHUDElement>(*It);
			if (Element)
			{
				Element->World = World;
				HUDElementInstances.Add(Element);
			}
		}
	}
}

void ARadiantWebViewHUD::DrawHUD()
{
	Super::DrawHUD();

	PreDrawHUD();

	const FVector2D ViewportSize(Canvas->SizeX, Canvas->SizeY);

	for (auto It = HUDElementInstances.CreateConstIterator(); It; ++It)
	{
		URadiantWebViewHUDElement *Element = *It;
		if (Element->bVisible)
		{
			Element->DrawHUD(Canvas, ViewportSize);
		}
	}

	PostDrawHUD();
}

void ARadiantWebViewHUD::Tick(float InDeltaSeconds)
{
	Super::Tick(InDeltaSeconds);

	float RealTime = FPlatformTime::Seconds() - GStartTime;
	float WorldTime = GetWorld()->GetTimeSeconds();

	for (auto It = HUDElementInstances.CreateConstIterator(); It; ++It)
	{
		(*It)->WebView->Tick(RealTime, WorldTime, InDeltaSeconds, GetWorld()->FeatureLevel);
	}
}

void ARadiantWebViewHUD::BeginPlay()
{
	check(GEngine->GameViewport);

	int ZOrder = 0;

	for (auto It = HUDElementInstances.CreateConstIterator(); It; ++It)
	{
		URadiantWebViewHUDElement* Element = *It;

		Element->WebView->SetNetMode(GetNetMode());
		Element->WebView->Start();
// 
// 		SAssignNew(Element->SWidget, SRadiantWebViewHUDElement).HUDOwner(this).HUDElement(Element);
// 		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(Element->Container, SWeakWidget).PossiblyNullContent(Element->SWidget.ToSharedRef()), ZOrder++);
// 		Element->SetSlateVisibility();

	}

	// Now tell the viewport client about ourselves.

	URadiantGameViewportClient *viewport = Cast<URadiantGameViewportClient>(GEngine->GameViewport);
	if (viewport)
	{
		viewport->SetHUD(this);
	} else
	{
		UE_LOG(RadiantUILog, Error, TEXT("URadiantGameViewportClient isn't the ViewportClient. Set this in the project settings to use HUD."));
	}

	Super::BeginPlay();
}

void ARadiantWebViewHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto It = HUDElementInstances.CreateConstIterator(); It; ++It)
	{
		URadiantWebViewHUDElement* Element = *It;

		Element->WebView.Reset();
		Element->MarkPendingKill();
	}

	HUDElementInstances.SetNum(0);

	Super::EndPlay(EndPlayReason);
}

void ARadiantWebViewHUD::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	static const int ArchiveVersion = 1;

	int Version = ArchiveVersion;
	Ar << Version;
}

FVector2D ARadiantWebViewHUD::GetViewportSize()
{
	return FVector2D(Canvas->SizeX, Canvas->SizeY);
}

URadiantWebViewHUDElement* ARadiantWebViewHUD::GetAffectedElement(FRadiantPointerEvent &event)
{
	for (auto It = HUDElementInstances.CreateConstIterator(); It; ++It)
	{
		URadiantWebViewHUDElement* Element = *It;

		if (Element->OnHitTest(event.GetScreenSpacePosition()))
		{
			return Element;
		}
	}

	return nullptr;
}

void ARadiantWebViewHUD::HandleMouseMove(FRadiantPointerEvent &event)
{
	URadiantWebViewHUDElement *element = GetAffectedElement(event);

	if (element!=nullptr)
	{
		element->HandleMouseMove(event);
	}
}

void ARadiantWebViewHUD::HandleMouseButtonDown(FRadiantPointerEvent &event)
{
	URadiantWebViewHUDElement *element = GetAffectedElement(event);

	if (element != nullptr)
	{
		element->HandleMouseButtonDown(event);
	}
}

void ARadiantWebViewHUD::HandleMouseButtonUp(FRadiantPointerEvent &event)
{
	URadiantWebViewHUDElement *element = GetAffectedElement(event);

	if (element != nullptr)
	{
		element->HandleMouseButtonUp(event);
	}
}

void ARadiantWebViewHUD::HandleMouseWheel(FRadiantPointerEvent &event)
{
	URadiantWebViewHUDElement *element = GetAffectedElement(event);

	if (element != nullptr)
	{
		element->HandleMouseWheel(event);
	}
}

void ARadiantWebViewHUD::HandleMouseDoubleClick(FRadiantPointerEvent &event)
{
	URadiantWebViewHUDElement *element = GetAffectedElement(event);

	if (element != nullptr)
	{
		element->HandleMouseDoubleClick(event);
	}
}

/*bool ARadiantWebViewHUD::HandleKeyDown(const FKey& Key)
{
	bool handled = false;
	if (TriggerKeys.Contains(Key))
	{
		handled = OnTriggerKeyDown(Key);
		if (!handled)
		{
			Received_OnTriggerKeyDown(Key, handled);
		}
	}
	
	return true;
}*/