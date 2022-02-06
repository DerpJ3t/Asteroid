#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "game.hpp"


Utils utils;
Game game;
//Screen width constants
const int screen_width = 640;
const int screen_height = 480;

const char* title = "Asteroid";
float delta_time = 0.1666;
std::vector <Entity> entities;

int main(int argc, char* args[])
{
	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		printf("Couldn't initialize SDL , Error : %s \n", SDL_GetError());
	}
	else
	{
		//Main loop flag
		bool running = true;

		//Event handler
		SDL_Event e;

		//Init SDL_image 
		if (!(IMG_Init(IMG_INIT_JPG)))
		{
			printf("Couldn't initialize SDL_image , Error : %s \n", IMG_GetError());
		}
		else
		{
			RenderWindow render_window(title, screen_width, screen_height);
			SDL_Texture* shooter_tex = render_window.loadTexture("res/shooter.png");
			SDL_SetRenderDrawColor(render_window.getRenderer(), 0, 0, 0, 0);
			float frame_begin_time = SDL_GetPerformanceCounter();

			Input input = {};
			while (running)
			{	

				//reset inputs;
				for (int i = 0; i < BUTTON_COUNT; i++)
				{
					input.buttons[i].is_down = false;
				}

				//Taking inputs 
				while (SDL_PollEvent(&e) != 0)
				{	
					
					//Users requests quit 
					if (e.type == SDL_QUIT)
					{
						running = false;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
							case SDLK_w:
								input.buttons[BUTTON_W].is_down = true;
								break;

							case SDLK_s:
								input.buttons[BUTTON_S].is_down = true;
								break;
							
							default:
								break;
						}

					}
				}
				
				//Set texture based on current keystate
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_UP])
				{
					input.buttons[BUTTON_UP].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_DOWN])
				{
					input.buttons[BUTTON_DOWN].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_LEFT])
				{
					input.buttons[BUTTON_LEFT].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					input.buttons[BUTTON_RIGHT].is_down = true;
				}

				//Simulate game 
				render_window.clear();
				game.simulate_shooter(&input, delta_time , render_window, shooter_tex); //rendering is done in game.hpp
				
				/*for (Entity& entity : entities)
				{
					render_window.render(entity);
				}*/
				render_window.update();

				float frame_end_time = SDL_GetPerformanceCounter();
				delta_time = utils.clamp_frame((frame_end_time - frame_begin_time) / SDL_GetPerformanceFrequency());
				
				frame_begin_time = frame_end_time;
			}

			render_window.close();
		}
		
	}

	return 0;
}
	


