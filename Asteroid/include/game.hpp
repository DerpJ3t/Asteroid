#pragma once
#define is_down(k) input->buttons[k].is_down


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
	void simulate_shooter(Input *input, float dt , RenderWindow& render_window, SDL_Texture* tex);
private:
	
};