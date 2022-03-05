#include "game.hpp"
#include <cmath>
#include <vector>
#include <Bullet.hpp>
#include <cstdlib>
#include <ctime>

Bullet bullet_function;
std::vector <Bullet> bullet_array;
std::vector <int> bullet_index;
std::vector <int> asteroids_index;
float shooter_dp_x = 0.0f , shooter_dp_y = 0.0f ;
double shooter_angle = 0.00; 
const float bullet_dp = 1000.0f;
float shooter_radius = shooter_size / 2.0f;
float asteroid_radius = asteroid_size / 2.0f;
float bullet_radius = bullet_size / 2.0f;


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

void Game::simulate_shooter(Entity& p_entity , Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex)
{
	float shooter_ddp_x = 0.0f;
	float shooter_ddp_y = 0.0f;

	shooter_ddp_x -= 0.025f * shooter_dp_x;
	shooter_ddp_y -= 0.025f * shooter_dp_y;

	float x = 0.0f;
	float y = 0.0f;


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

	x += shooter_dp_x * dt + 0.5f * (shooter_ddp_x * dt * dt);
	y += shooter_dp_y * dt + 0.5f * (shooter_ddp_y * dt * dt);

	p_entity.move(x, y);
	if (p_entity.pos.x  < 8)
	{	
		p_entity.pos_reset(8, p_entity.pos.y);
		/*shooter_ddp_x = 0;
		shooter_ddp_y = 0;*/
		shooter_dp_x = 0; 
		shooter_dp_y = 0; 
	}
	if (p_entity.pos.x + shooter_size > (float)screen_width )
	{	
		p_entity.pos_reset((float)screen_width - shooter_size  , p_entity.pos.y);
		/*shooter_ddp_x = 0;
		shooter_ddp_y = 0;*/
		shooter_dp_x = 0;
		shooter_dp_y = 0; 
	}
	if (p_entity.pos.y  < 8)
	{	
		p_entity.pos_reset(p_entity.pos.x , 8);
		/*shooter_ddp_x = 0; 
		shooter_ddp_y = 0; */
		shooter_dp_x = 0; 
		shooter_dp_y = 0; 
	}
	if (p_entity.pos.y + shooter_size > screen_height)
	{	
		p_entity.pos_reset(p_entity.pos.x, (float)screen_height - shooter_size);
		/*shooter_ddp_x = 0;
		shooter_ddp_y = 0;*/
		shooter_dp_x = 0; 
		shooter_dp_y = 0; 
	}

	shooter_angle = atan2(input->Mouse2f.y - p_entity.pos.y, input->Mouse2f.x - p_entity.pos.x) * 180 / M_PI ;  //rad = 180 / PI
	p_entity.rotate(shooter_angle);
}

void Game::simulate_bullet(Entity& shooter , Input* input, float dt, RenderWindow& render_window, SDL_Texture* tex)
{	
	
	if (is_down(MOUSE_DOWN))
	{	
		Bullet bul(Vector2f(shooter.pos.x, shooter.pos.y), tex );
		bul.launch_angle  = (trig_atan(shooter.pos.y - input->Mouse2f.y, shooter.pos.x - input->Mouse2f.x)) + M_PI  ;
		bullet_array.push_back(bul);
	}
	for (int i = 0; i < bullet_array.size(); i++)
	{
		float x(0.0f), y(0.0f);
		float dp_x = (float)bullet_dp * cos(bullet_array[i].launch_angle);
		float dp_y = (float)bullet_dp * sin(bullet_array[i].launch_angle);
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

bool Game::bullet_asteroid_collision(float bullet_x, float bullet_y, int bullet_radius, float asteroid_x, float asteroid_y, int asteroid_radius)
{
	float xDist = asteroid_x - bullet_x;
	float yDist = asteroid_y - bullet_y;
	float dist = (float)sqrt(pow(xDist, 2) + pow(yDist, 2));
	if (dist < bullet_radius + asteroid_radius)
	{
		return true;
	}
	return false;
}

//void Game::simulate_asteroid(Entity &asteroid)
//{	
//
//	for (int i = 0; i < bullet_array.size();)
//	{	
//			bool collide = bullet_asteroid_collision(bullet_array[i].pos.x, bullet_array[i].pos.y, bullet_radius, asteroid.pos.x, asteroid.pos.y, asteroid_radius);
//			if (collide)
//			{
//				bullet_array.erase(bullet_array.begin() + i);
//			}
//			else
//			{
//				i++; 
//			}
//	}
//}

void Game::simulate_asteroid(std::vector <Entity>& asteroids)
{

	for (int i = 0; i < bullet_array.size();)
	{	
		bool collide_bullets = false;
		for (int j = 0; j < asteroids.size();)
		{
			bool collide_asteroids = bullet_asteroid_collision(bullet_array[i].pos.x, bullet_array[i].pos.y, bullet_radius, asteroids[j].pos.x, asteroids[j].pos.y, asteroid_radius);
			if (collide_asteroids)
			{
				asteroids.erase(asteroids.begin() + j);
				collide_bullets = true;
			}
			else
			{
				j++;
			}
		}
		if (collide_bullets)
		{
			bullet_array.erase(bullet_array.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

