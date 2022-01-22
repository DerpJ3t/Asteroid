#pragma once
#define is_down(d) input->buttons[d].is_down
#define is_changed(d) input->buttons[d].is_changed && input->buttons[d].is_down


#include <SDL.h>
#include <SDL_image.h>
#include "utils.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "Math.hpp"
class Game
{
public:
	void simulate_shooter(Entity& p_entity , Input *input, float dt);
private:
	
};