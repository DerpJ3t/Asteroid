#include "game.hpp"


//Equation of motions
// v = u + at;
// s = ut + 1/2at^2


void Game::simulate_shooter(Entity& p_entity ,Input* input, float dt)
{	

	p_entity.getpos().ddp_x = 0.0f;
	p_entity.getpos().ddp_y = 0.0f;


	if (is_down(BUTTON_UP))
	{
		p_entity.getpos().ddp_y += 10.0f;
	}
	if (is_down(BUTTON_DOWN))
	{
		p_entity.getpos().ddp_y -= 10.0f;
	}
	if (is_down(BUTTON_LEFT))
	{
		p_entity.getpos().ddp_x -= 10.0f;
	}
	if (is_down(BUTTON_RIGHT))
	{
		p_entity.getpos().ddp_x += 10.0f;
	}
}