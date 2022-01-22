#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

struct Vector2f
{
	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
	{
	}

	void print()
	{
		printf("%f , %f", x, y);
	}
	float x, y;
	float dp_x , dp_y;
	float ddp_x , ddp_y;
};