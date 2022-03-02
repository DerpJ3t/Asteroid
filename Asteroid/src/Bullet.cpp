#include "Bullet.hpp"
#include "utils.hpp"


Bullet::Bullet(Vector2f initial_pos, SDL_Texture* p_tex)
	:tex(p_tex), launch_angle(0.0f), pos_x(0.0f), pos_y(0.0f)
{
	pos_x += initial_pos.x;
	pos_y += initial_pos.y;
}

void Bullet::move(float x, float y)
{
	pos_x += x;
	pos_y += y;
}

bool Bullet::out_of_screen(Bullet& bullet)
{
	if (bullet.pos_x + bullet_size > screen_width)
	{
		return true;
	}
	if (bullet.pos_x - bullet_size < 0)
	{
		return true;
	}
	if (bullet.pos_y + bullet_size > screen_height)
	{
		return true;
	}
	if (bullet.pos_y - bullet_size < 0)
	{
		return true;
	}

	return false;
}


