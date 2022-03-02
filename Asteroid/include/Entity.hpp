class RenderWindow;

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"

class Entity
{

public:
	Entity(Vector2f pos , SDL_Texture* p_tex ,double p_angle, int size);
	double get_angle()
	{
		return rotation_angle;
	}
	friend class RenderWindow;

	
	

private:

	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	double rotation_angle;
	int size;
};