#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

struct Vector2f
{
	Vector2f()
	{}

	Vector2f(float p_x, float p_y, double p_angle)
		:x(p_x), y(p_y), angle(p_angle)
	{}

	void print()
	{
		printf("%f , %f , %d" , x, y, angle);
	}
	float x, y;
	double angle;
	
};