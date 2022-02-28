#include "game.hpp"
#include <cmath>
#include <iostream>
#include <vector>

std::vector<Entity> bullets;

float shooter_pos_x = 0.0f, shooter_pos_y = 0.0f ;
float shooter_dp_x = 0.0f , shooter_dp_y = 0.0f ;
double shooter_angle = 0.00; 
float bullet_dp = 30.f;



//Equation of motions
// v = u + at;
// s = ut + 1/2at^2

void Game::simulate_bullet_movement(Entity& p_bullet, float dt)
{	
	double angle = p_bullet.get_angle();
	float dp_x = SDL_cosf(angle) * bullet_dp;
	float dp_y = SDL_sinf(angle) * bullet_dp;
	
	p_bullet.getpos().x += dp_x * dt;
	p_bullet.getpos().y += dp_y * dt;
}
void Game::simulate_shooter(Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex)
{
	float shooter_ddp_x = 0.0f;
	float shooter_ddp_y = 0.0f;

	shooter_ddp_x -= 0.025f * shooter_dp_x;
	shooter_ddp_y -= 0.025f * shooter_dp_y;


	if (is_down(BUTTON_W))
	{
		shooter_ddp_y -= 100.0f;
	}
	if (is_down(BUTTON_S))
	{
		shooter_ddp_y += 100.0f;
	}
	if (is_down(BUTTON_A))
	{
		shooter_ddp_x -= 100.0f;
	}
	if (is_down(BUTTON_D))
	{
		shooter_ddp_x += 100.0f;
	}

	shooter_dp_x += shooter_ddp_x * dt;
	shooter_dp_y += shooter_ddp_y * dt;

	shooter_pos_x += shooter_dp_x * dt + 0.5f * (shooter_ddp_x * dt * dt);
	shooter_pos_y += shooter_dp_y * dt + 0.5f * (shooter_ddp_y * dt * dt);


	if (shooter_pos_x < 0)
	{
		shooter_pos_x = 0;
		/*shooter_ddp_x = 0;
		shooter_ddp_y = 0;*/
		shooter_dp_x = 0; 
		shooter_dp_y = 0; 
	}
	if (shooter_pos_x > (float)screen_width - shooter_size)
	{
		shooter_pos_x = (float)screen_width - shooter_size;
		/*shooter_ddp_x = 0;
		shooter_ddp_y = 0;*/
		shooter_dp_x = 0;
		shooter_dp_y = 0; 
	}
	if (shooter_pos_y < 0)
	{
		shooter_pos_y = 0; 
		/*shooter_ddp_x = 0; 
		shooter_ddp_y = 0; */
		shooter_dp_x = 0; 
		shooter_dp_y = 0; 
	}
	if (shooter_pos_y > screen_height - shooter_size)
	{
		shooter_pos_y = (float)screen_height - shooter_size;
		/*shooter_ddp_x = 0;
		shooter_ddp_y = 0;*/
		shooter_dp_x = 0; 
		shooter_dp_y = 0; 
	}

	shooter_angle = atan2(input->Mouse2f.y - shooter_pos_y, input->Mouse2f.x - shooter_pos_x) * 180 / M_PI + 90; //plus 90 because sdl axis works differently //rad = 180 / PI

	//Render
	Entity shooter(Vector2f(shooter_pos_x, shooter_pos_y), tex, shooter_angle, shooter_size);
	render_window.render(shooter);

}


void Game::simulate_bullet(Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex)
{
	if (is_down(MOUSE_DOWN))
	{	
		double launch_angle = shooter_angle = atan2(input->Mouse2f.y - shooter_pos_y, input->Mouse2f.x - shooter_pos_x) * 180 / M_PI + 90;
		Entity bul(Vector2f(shooter_pos_x, shooter_pos_y), tex, launch_angle, bullet_size);
		bullets.push_back(bul);
	}
	for (Entity& bullet : bullets)
	{	
		simulate_bullet_movement(bullet, dt);
		render_window.render(bullet);
	}
}
