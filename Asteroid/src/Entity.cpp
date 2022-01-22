#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos) , tex(p_tex)
{
	currentFrame.x = pos.x; 
	currentFrame.y = pos.y;
	currentFrame.w = 0;
	currentFrame.h = 0; 
	
}
