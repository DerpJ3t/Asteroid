#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* p_tex, int p_size)
	:pos(pos), tex(p_tex), size(p_size)
{
	
}
void Entity::move(float x, float y)
{
	pos.x += x;
	pos.y += y;
}

void Entity::rotate(double p_angle)
{
	rotation_angle = p_angle;
}

void Entity::pos_reset(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

