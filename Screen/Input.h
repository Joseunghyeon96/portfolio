#pragma once
class Input
{
	static INPUT_RECORD InputRecord[128];
	static DWORD Events;
	static bool evaluated;
	static bool gotMouseEvent;
	static bool gotKeyEvent;
	static Vector2 mousePosition;
	static WORD vKeyCode;

	static void GetEvent();

public:

	static void EndOfFrame();

	static void Initialize();

	static bool GetMouseEvent(Vector2& pos);

	static bool GetKeyEvent(WORD& keyCode);

	static bool GetKeyDown(KeyCode key);
};

