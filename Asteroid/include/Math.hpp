#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

struct Vector2f
{
	Vector2f()
	{}

	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
	{}

	void print()
	{
		printf("%f , %f \n", x, y);
	}
	float x, y;
	
};