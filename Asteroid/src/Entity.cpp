#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, double p_angle, int p_size)
	:pos(p_pos) , tex(p_tex), rotation_angle(p_angle), size(p_size)
{
	currentFrame.x = pos.x; 
	currentFrame.y = pos.y;
	
}
