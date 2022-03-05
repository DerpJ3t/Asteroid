#include "Bullet.hpp"
#include "utils.hpp"


Bullet::Bullet(Vector2f initial_pos, SDL_Texture* p_tex)
	:tex(p_tex), launch_angle(0.0f) 
{
	pos.x = initial_pos.x;
	pos.y = initial_pos.y;
}

void Bullet::move(float x, float y)
{
	pos.x += x;
	pos.y += y;
}

bool Bullet::out_of_screen(Bullet& bullet)
{
	if (bullet.pos.x + bullet_size > screen_width)
	{
		return true;
	}
	if (bullet.pos.x - bullet_size < 0)
	{
		return true;
	}
	if (bullet.pos.y + bullet_size > screen_height)
	{
		return true;
	}
	if (bullet.pos.y - bullet_size < 0)
	{
		return true;
	}

	return false;
}


