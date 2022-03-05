#pragma once
#define is_down(k) input->states[k].is_down


#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "utils.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "renderwindow.hpp"
class Game
{
public:
	void simulate_shooter(Entity& p_entity, Input* input , float dt , RenderWindow &render_window ,SDL_Texture* p_tex);
	void simulate_bullet(Entity& shooter , Input* input, float dt, RenderWindow& render_window, SDL_Texture* p_tex);
	void simulate_asteroid(std::vector <Entity>& asteroids);
	bool bullet_asteroid_collision(float bullet_x, float bullet_y, int bullet_radius, float asteroid_x, float asteroid_y, int asteroid_radius);
private:
};