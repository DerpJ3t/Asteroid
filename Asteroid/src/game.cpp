#include "game.hpp"

float shooter_pos_x = 0, shooter_pos_y = 0 ;
float shooter_dp_x , shooter_dp_y;
double shooter_angle = 0; 


//Equation of motions
// v = u + at;
// s = ut + 1/2at^2


void Game::simulate_shooter(Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex)
{
	float shooter_ddp_x = 0.0f;
	float shooter_ddp_y = 0.0f;

	shooter_ddp_x -= shooter_dp_x * 0.5f; //friction
	shooter_ddp_y -= shooter_dp_y * 0.5f;

	if (is_down(BUTTON_UP))
	{
		shooter_ddp_y -= 100.0f;
	}
	if (is_down(BUTTON_DOWN))
	{
		shooter_ddp_y += 100.0f;
	}
	if (is_down(BUTTON_LEFT))
	{
		shooter_ddp_x -= 100.0f;
	}
	if (is_down(BUTTON_RIGHT))
	{
		shooter_ddp_x += 100.0f;
	}
	
	if (is_down(BUTTON_W))
	{
		shooter_angle += 20;
	}

	if (is_down(BUTTON_S))
	{
		shooter_angle -= 20;
	}
	shooter_dp_x += (shooter_ddp_x * dt);
	shooter_pos_x += (shooter_dp_x * dt) + (shooter_ddp_x * dt * dt) * 0.5f;
	shooter_dp_y += (shooter_ddp_y * dt);
	shooter_pos_y += (shooter_dp_y * dt) + (shooter_ddp_y * dt * dt) * 0.5f;

	
	if (shooter_pos_x < 0)
	{
		shooter_pos_x = 0;
	}
	if (shooter_pos_x + 32 > screen_width) {
		shooter_pos_x = screen_width - 32;
	}
	if (shooter_pos_y < 0)
	{
		shooter_pos_y = 0;
	}
	if (shooter_pos_y + 32 > screen_height) 
	{
		shooter_pos_y = screen_height - 32;
	}

	//Render
	Entity shooter(Vector2f(shooter_pos_x, shooter_pos_y, shooter_angle), tex);
	render_window.render(shooter);

}