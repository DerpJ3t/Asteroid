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
	void simulate_shooter(Input* input , float dt , RenderWindow &render_window ,SDL_Texture* p_tex);
	void simulate_bullet(Input* input, float dt, RenderWindow& render_window, SDL_Texture* p_tex);
	void bullet_update(float* p_x,float* p_y, double p_angle);
private:
};