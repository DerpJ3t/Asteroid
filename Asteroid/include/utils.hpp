#pragma once 

extern const int screen_width;
extern const int screen_height;

#define process_single_key(d, sdl_key)\
case sdl_key:{\
	input.buttons[d].is_changed = true;\
}break;\

#define process_continuous_press(d, sdl_key)\
if(keystate[sdl_key])\
{\
	input.buttons[d].is_down = true;\
}\

struct Utils
{
	float clamp_frame(float dt);
};