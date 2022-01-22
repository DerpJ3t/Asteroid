class RenderWindow;
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f pos , SDL_Texture* p_tex);
	Vector2f& getpos()
	{
		return pos;
	}
	friend class RenderWindow;

private:

	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};