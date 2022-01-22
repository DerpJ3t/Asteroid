#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "renderwindow.hpp"
#include "game.hpp"


Utils utils;
Vector2f shooterpos;
Vector2f asteroidpos;
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
			SDL_Texture* asteroid_tex = render_window.loadTexture("res/asteroid.png");
			for (int y = 0; y <= screen_height - 32; y += 32)
			{
				for (int x = 0; x<= screen_width - 32; x += 32)
				{
					Entity platform(Vector2f(x , y), asteroid_tex);
					entities.push_back(platform);
				}
			}
			Entity shooter(Vector2f(0,0 ), shooter_tex);
			SDL_SetRenderDrawColor(render_window.getRenderer(), 0, 0, 0, 0);
			float frame_begin_time = SDL_GetPerformanceCounter();

			Input input = {};
			while (running)
			{	
				//Continuous presses
				const Uint8* keystate = SDL_GetKeyboardState(NULL);
				process_continuous_press(BUTTON_UP, SDL_SCANCODE_UP);
				process_continuous_press(BUTTON_DOWN, SDL_SCANCODE_DOWN);
				process_continuous_press(BUTTON_LEFT, SDL_SCANCODE_LEFT);
				process_continuous_press(BUTTON_RIGHT, SDL_SCANCODE_RIGHT);
				process_continuous_press(BUTTON_W, SDL_SCANCODE_W);
				process_continuous_press(BUTTON_A, SDL_SCANCODE_A);
				process_continuous_press(BUTTON_S, SDL_SCANCODE_S);
				process_continuous_press(BUTTON_D, SDL_SCANCODE_D);

				//Taking inputs 
				while (SDL_PollEvent(&e) != 0)
				{	

					//Users requests quit 
					if (e.type == SDL_QUIT)
					{
						running = false;
					}
					else if(e.type == SDL_KEYDOWN)
					{	
						switch (e.key.keysym.sym)
						{
							process_single_key(BUTTON_UP, SDLK_UP);
							process_single_key(BUTTON_DOWN, SDLK_DOWN);
							process_single_key(BUTTON_LEFT, SDLK_LEFT);
							process_single_key(BUTTON_UP, SDLK_RIGHT);
							process_single_key(BUTTON_W, SDLK_w);
							process_single_key(BUTTON_A, SDLK_a);
							process_single_key(BUTTON_S, SDLK_s);
							process_single_key(BUTTON_D, SDLK_d);
						}
						
					}
				}

				//Simulate game 
				render_window.clear();
				game.simulate_shooter(shooter,&input, delta_time); //rendering is done in game.hpp
				
				/*for (Entity& entity : entities)
				{
					render_window.render(entity);
				}*/
				render_window.render(shooter);
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
	


