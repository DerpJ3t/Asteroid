#include "game.hpp"
#include <cmath>
#include <vector>
#include <Bullet.hpp>

Bullet bullet_function;
std::vector <Bullet> bullet_array;
float shooter_pos_x = 0.0f, shooter_pos_y = 0.0f ;
float shooter_dp_x = 0.0f , shooter_dp_y = 0.0f ;
double shooter_angle = 0.00; 
const float bullet_dp = 1000.0f;






//Equation of motions
// v = u + at;
// s = ut + 1/2at^2

//void Game::simulate_bullet_movement(Entity& p_bullet, float dt)
//{	
//	double angle = p_bullet.get_angle();
//	float dp_x = bullet_dp;
//	float dp_y =  bullet_dp;
//	
//	p_bullet.getpos().x += dp_x * dt;
//	p_bullet.getpos().y += dp_y * dt;
//}

void Game::simulate_shooter(Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex)
{
	float shooter_ddp_x = 0.0f;
	float shooter_ddp_y = 0.0f;

	shooter_ddp_x -= 0.025f * shooter_dp_x;
	shooter_ddp_y -= 0.025f * shooter_dp_y;


	if (is_down(BUTTON_W))
	{
		shooter_ddp_y -= 500.0f;
	}
	if (is_down(BUTTON_S))
	{
		shooter_ddp_y += 500.0f;
	}
	if (is_down(BUTTON_A))
	{
		shooter_ddp_x -= 500.0f;
	}
	if (is_down(BUTTON_D))
	{
		shooter_ddp_x += 500.0f;
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

	shooter_angle = atan2(input->Mouse2f.y - shooter_pos_y, input->Mouse2f.x - shooter_pos_x) * 180 / M_PI ;  //rad = 180 / PI

	//Render
	Entity shooter(Vector2f(shooter_pos_x, shooter_pos_y), tex, shooter_angle, shooter_size);
	render_window.render(shooter);

}

void Game::simulate_bullet(Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex)
{	
	
	if (is_down(MOUSE_DOWN))
	{	
		Bullet bul(Vector2f(shooter_pos_x, shooter_pos_y), tex);
		bul.launch_angle  = (trig_atan(shooter_pos_y - input->Mouse2f.y, shooter_pos_x - input->Mouse2f.x)) + M_PI  ;
		bullet_array.push_back(bul);
	}
	for (int i = 0; i < bullet_array.size(); i++)
	{
		float x(0.0f), y(0.0f);
		float dp_x = bullet_dp * cos(bullet_array[i].launch_angle);
		float dp_y = bullet_dp * sin(bullet_array[i].launch_angle);
		x += dp_x * dt;
		y += dp_y * dt;
		bullet_array[i].move(x, y);
		if (bullet_function.out_of_screen(bullet_array[i]))
		{
			bullet_array.erase(bullet_array.begin() + i); // remove bullet upon collision;
		}
	}
	for (Bullet& bullet : bullet_array)
	{
		render_window.render_bullet(bullet);
	}
}
