#pragma once 

extern const int screen_width;
extern const int screen_height;

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