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

static double trig_atan(float y, float x)
{	
	if (x >= 0 && y >= 0) //first quadrant
	{
		return atan(y / x);
	}
	if (x < 0 && y > 0) //second quadrant
	{
		return atan(y / x) + M_PI;
	}
	if (x < 0 && y < 0) //third quadrant
	{
		return atan(y / x) + M_PI;
	}
	
	return atan(y / x) + 2 * M_PI; // fourth quadrant
	
}