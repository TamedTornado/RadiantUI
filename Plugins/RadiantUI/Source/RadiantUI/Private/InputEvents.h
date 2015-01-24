// (C) 2015 Jason Maskell
#pragma once
#include "InputCoreTypes.h"
#include "../CefRuntime/API/CefRuntimeAPI.h"

/*
	These input events are cadged from the Slate input events, with some cuts (such as pointer index, anything related to Touch). 
	If those are needed they can be put back.

	The other changes are accomodations/convenience methods for interacting with CEF.

*/

struct FRadiantInputEvent
{
protected:
	FModifierKeysState ModifierKeys;
	bool bIsRepeat;

public:
	FRadiantInputEvent(const FModifierKeysState& InModifierKeys, const bool bInIsRepeat): ModifierKeys(InModifierKeys), bIsRepeat(bInIsRepeat) { }
	virtual ~FRadiantInputEvent() { }

	/**
	 * Returns whether or not this character is an auto-repeated keystroke
	 *
	 * @return  True if this character is a repeat
	 */
	bool IsRepeat() const
	{
		return bIsRepeat;
	}

	/**
	 * Returns true if either shift key was down when this event occurred
	 *
	 * @return  True if shift is pressed
	 */
	bool IsShiftDown() const
	{
		return ModifierKeys.IsShiftDown();
	}

	/**
	 * Returns true if left shift key was down when this event occurred
	 *
	 * @return True if left shift is pressed.
	 */
	bool IsLeftShiftDown() const
	{
		return ModifierKeys.IsLeftShiftDown();
	}

	/**
	 * Returns true if right shift key was down when this event occurred
	 *
	 * @return True if right shift is pressed.
	 */
	bool IsRightShiftDown() const
	{
		return ModifierKeys.IsRightShiftDown();
	}

	/**
	 * Returns true if either control key was down when this event occurred
	 *
	 * @return  True if control is pressed
	 */
	bool IsControlDown() const
	{
		return ModifierKeys.IsControlDown();
	}

	/**
	 * Returns true if left control key was down when this event occurred
	 *
	 * @return  True if left control is pressed
	 */
	bool IsLeftControlDown() const
	{
		return ModifierKeys.IsLeftControlDown();
	}

	/**
	 * Returns true if right control key was down when this event occurred
	 *
	 * @return  True if right control is pressed
	 */
	bool IsRightControlDown() const
	{
		return ModifierKeys.IsRightControlDown();
	}

	/**
	 * Returns true if either alt key was down when this event occurred
	 *
	 * @return  True if alt is pressed
	 */
	bool IsAltDown() const
	{
		return ModifierKeys.IsAltDown();
	}

	/**
	 * Returns true if left alt key was down when this event occurred
	 *
	 * @return  True if left alt is pressed
	 */
	bool IsLeftAltDown() const
	{
		return ModifierKeys.IsLeftAltDown();
	}

	/**
	 * Returns true if right alt key was down when this event occurred
	 *
	 * @return  True if right alt is pressed
	 */
	bool IsRightAltDown() const
	{
		return ModifierKeys.IsRightAltDown();
	}

	/**
	 * Returns true if either command key was down when this event occurred
	 *
	 * @return  True if command is pressed
	 */
	bool IsCommandDown() const
	{
		return ModifierKeys.IsCommandDown();
	}

	/**
	 * Returns true if left command key was down when this event occurred
	 *
	 * @return  True if left command is pressed
	 */
	bool IsLeftCommandDown() const
	{
		return ModifierKeys.IsLeftCommandDown();
	}

	/**
	 * Returns true if right command key was down when this event occurred
	 *
	 * @return  True if right command is pressed
	 */
	bool IsRightCommandDown() const
	{
		return ModifierKeys.IsRightCommandDown();
	}

	/**
	 * Returns true if caps lock was on when this event occurred
	 * 
	 * @return True if caps lock is on
	 */
	bool AreCapsLocked() const
	{
		return ModifierKeys.AreCapsLocked();
	}
};

struct FRadiantKeyEvent : public FRadiantInputEvent
{
private:
	// Name of the key that was pressed.
	FKey Key;

	// The character code of the key that was pressed.  Only applicable to typed character keys, 0 otherwise.
	uint32 CharacterCode;

	// Original key code received from hardware before any conversion/mapping
	uint32 KeyCode;
public:

	FRadiantKeyEvent(const FKey InKey,
		const FModifierKeysState& InModifierKeys,
		const bool bInIsRepeat,
		const uint32 InCharacterCode,
		const uint32 InKeyCode) : FRadiantInputEvent(InModifierKeys, bInIsRepeat), Key(InKey), CharacterCode(InCharacterCode), KeyCode(InKeyCode) { }

	virtual ~FRadiantKeyEvent() { }

	/**
	 * Returns the name of the key for this event
	 *
	 * @return  Key name
	 */
	FKey GetKey() const
	{
		return Key;
	}

	/**
	 * Returns the character code for this event.
	 *
	 * @return  Character code or 0 if this event was not a character key press
	 */
	uint32 GetCharacter() const
	{
		return CharacterCode;
	}

	/**
	 * Returns the key code received from hardware before any conversion/mapping.
	 *
	 * @return  Key code received from hardware
	 */
	uint32 GetKeyCode() const
	{
		return KeyCode;
	}
};

struct FRadiantPointerEvent: public FRadiantInputEvent
{
private:
	FVector2D ScreenSpacePosition;
	FVector2D LastScreenSpacePosition;
	FVector2D CursorDelta;
	const TSet<FKey>& PressedButtons;
	FKey EffectingButton;
	FVector2D WheelOrGestureDelta;
public:
	FRadiantPointerEvent(
		const FVector2D& InScreenSpacePosition,
		const FVector2D& InLastScreenSpacePosition,
		const TSet<FKey>& InPressedButtons,
		FKey InEffectingButton,
		float InWheelDelta,
		const FModifierKeysState& InModifierKeys
		)
		: FRadiantInputEvent(InModifierKeys, false)
		, ScreenSpacePosition(InScreenSpacePosition)
		, LastScreenSpacePosition(InLastScreenSpacePosition)
		, CursorDelta(InScreenSpacePosition - InLastScreenSpacePosition)
		, PressedButtons(InPressedButtons)
		, EffectingButton(InEffectingButton)
		, WheelOrGestureDelta(0.0f, InWheelDelta)
	{ }

	/** @return The position of the cursor in screen space */
	const FVector2D& GetScreenSpacePosition() const { return ScreenSpacePosition; }

	/** @return The position of the cursor in screen space last time we handled an input event */
	const FVector2D& GetLastScreenSpacePosition() const { return LastScreenSpacePosition; }

	/** @return the distance the mouse traveled since the last event was handled. */
	FVector2D GetCursorDelta() const { return CursorDelta; }

	/** Mouse buttons that are currently pressed */
	bool IsMouseButtonDown(FKey MouseButton) const { return PressedButtons.Contains(MouseButton); }

	/** Mouse button that caused this event to be raised (possibly EB_None) */
	FKey GetEffectingButton() const { return EffectingButton; }

	/** How much did the mouse wheel turn since the last mouse event */
	float GetWheelDelta() const { return WheelOrGestureDelta.Y; }

	ECefRuntimeMouseButton GetCEFMouseButton()
	{
		FKey Key = GetEffectingButton();
		if (Key == EKeys::LeftMouseButton)
		{
			return CEFRT_MouseLeft;
		}
		if (Key == EKeys::RightMouseButton)
		{
			return CEFRT_MouseRight;
		}

		check(Key == EKeys::MiddleMouseButton);
		return CEFRT_MouseMiddle;
	}

	int32 GetCEFModifiers()
	{
		unsigned int result = 0;
		if (IsAltDown())
		{
			result |= CEFRT_AltDown;
		}

		if (IsControlDown())
		{
			result |= CEFRT_ControlDown;
		}

		if (IsShiftDown())
		{
			result |= CEFRT_ShiftDown;
		}

		if (IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			result |= CEFRT_LeftMouseButton;
		}

		if (IsMouseButtonDown(EKeys::RightMouseButton))
		{
			result |= CEFRT_RightMouseButton;
		}

		if (IsMouseButtonDown(EKeys::MiddleMouseButton))
		{
			result |= CEFRT_MiddleMouseButton;
		}

		return result;
	}
};
