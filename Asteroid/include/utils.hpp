#pragma once 
#include <SDL.h>

extern const int screen_width;
extern const int screen_height;
extern const int shooter_size;
extern const int bullet_size;
extern const int asteroid_size;
extern float shooter_pos_x;
extern float shooter_pos_y;

#define key_press(d, sdl_key)\
{\
	case sdl_key: {\
		input.buttons[d].is_down = true;\
	}break; \
}




struct Utils
{
	float clamp_frame(float dt);
};