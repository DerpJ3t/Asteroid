#pragma once
#define is_down(k) input->states[k].is_down


#include <SDL.h>
#include <SDL_image.h>
#include "utils.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "renderwindow.hpp"
class Game
{
public:
	void simulate_shooter(Input* input , float dt , RenderWindow &render_window ,SDL_Texture* tex);
	void simulate_bullet(Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex);
	void simulate_bullet_movement(Entity& p_bullet,  float dt);
private:
};