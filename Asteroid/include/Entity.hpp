class RenderWindow;
class Game;

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"

class Entity
{

public:
	Entity(Vector2f pos , SDL_Texture* p_tex , int size);
	double get_angle()
	{
		return rotation_angle;
	}
	void move(float x, float y);
	void rotate(double p_angle);
	void pos_reset(float x, float y);
	friend class RenderWindow;
	friend class Game;
	
	

private:

	Vector2f pos;
	SDL_Texture* tex;
	double rotation_angle;
	int size;
};