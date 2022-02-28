#pragma once

struct InputState
{
	bool is_down;
};

struct MousePos
{
	int x, y;
};



enum InputStates
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_W,
	BUTTON_A,
	BUTTON_S,
	BUTTON_D,
	MOUSE_DOWN,
	BUTTON_COUNT
};

struct Input
{
	InputState states[BUTTON_COUNT];
	MousePos Mouse2f;
};