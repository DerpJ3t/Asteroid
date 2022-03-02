#pragma once
#include <Math.hpp>
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow;

class Bullet
{
public:
	double launch_angle;
	Bullet()
	{

	}
	Bullet(Vector2f initial_pos, SDL_Texture* p_tex);
	void move(float pos_x, float pos_y);
	bool out_of_screen(Bullet& bullet);

	friend class RenderWindow;
private:
	Vector2f pos;
	float pos_x, pos_y;
	SDL_Texture* tex;

};