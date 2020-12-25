#include "stdafx.h"
#include "Input.h"

INPUT_RECORD Input::InputRecord[128];
DWORD Input::Events;

bool Input::evaluated = false;
bool Input::gotMouseEvent = false;
bool Input::gotKeyEvent = false;
Vector2 Input::mousePosition{ -1, -1 };
WORD Input::vKeyCode{ 0 };

void Input::GetEvent()
{
	evaluated = true;
	DWORD numEvents = 0;

	GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &numEvents);
	if (!numEvents) return;

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), InputRecord, numEvents, &Events);
	for (int i = 0; i < Events; i++) {
		if (InputRecord[i].EventType == MOUSE_EVENT) {
			if (InputRecord[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				COORD coord;
				coord.X = InputRecord[i].Event.MouseEvent.dwMousePosition.X;
				coord.Y = InputRecord[i].Event.MouseEvent.dwMousePosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				mousePosition.x = InputRecord[i].Event.MouseEvent.dwMousePosition.X;
				mousePosition.y = InputRecord[i].Event.MouseEvent.dwMousePosition.Y;
				gotMouseEvent = true;
			}
		}
		else if (InputRecord[i].EventType == KEY_EVENT) {
			if (InputRecord[i].Event.KeyEvent.bKeyDown) {
				vKeyCode = InputRecord[i].Event.KeyEvent.wVirtualKeyCode;
				gotKeyEvent = true;
			}
		}
	}
}

void Input::EndOfFrame()
{
	evaluated = false;
	gotMouseEvent = false;
	gotKeyEvent = false;
}

void Input::Initialize()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

	EndOfFrame();
}

bool Input::GetMouseEvent(Vector2 & pos)
{
	if (evaluated == false) GetEvent();

	if (gotMouseEvent == true) {
		pos = mousePosition;
		return true;
	}
	return false;
}

bool Input::GetKeyEvent(WORD & keyCode)
{
	if (evaluated == false) GetEvent();

	if (gotKeyEvent == true) {
		keyCode = vKeyCode;
		return true;
	}
	return false;
}

bool Input::GetKeyDown(KeyCode key)
{
	if (evaluated == false) GetEvent();

	if (gotKeyEvent == true) return keyCodeTable[(int)key] == vKeyCode;
	return false;
}
