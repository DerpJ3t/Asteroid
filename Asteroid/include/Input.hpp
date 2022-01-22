#pragma once

struct ButtonState
{
	bool is_down;
	bool is_changed;
};

enum KeyPresses
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_W,
	BUTTON_A,
	BUTTON_S,
	BUTTON_D,
	BUTTON_COUNT
};

struct Input
{
	ButtonState buttons[BUTTON_COUNT];
};