#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "game.hpp"

Utils utils;
Game game;
//Screen width constants
const int screen_width = 640;
const int screen_height = 480;

const int shooter_size = 32;
const int bullet_size = 8;
const int asteroid_size = 40;


const char* title = "Asteroid";
float delta_time = 0.1666f;
std::vector <Entity> asteroids;


int main(int argc, char* args[])
{
	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
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
		else if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
		else
		{	

			srand(time(NULL)); //generate seed for rand()
			int asteroid_num = (rand() % 15 );

			//Randomly spawn shooter
			float shooter_pos_x = (float)(rand() % (screen_width - 0 + 1));
			float shooter_pos_y = (float)(rand() % (screen_height - 0 + 1));

			
			RenderWindow render_window(title, screen_width, screen_height);

			//Load entity textures
			SDL_Texture* shooter_tex = render_window.loadTexture("res/shooter.png");
			SDL_Texture* bullet_tex = render_window.loadTexture("res/bullet.png");
			SDL_Texture* asteroid_tex = render_window.loadTexture("res/asteroid.png");

			//Load sound effects
			Mix_Chunk* launch_sound = render_window.loadAudio("res/launch_sound.wav");

			SDL_SetRenderDrawColor(render_window.getRenderer(), 0, 0, 0, 0);
			Uint64 frame_begin_time = SDL_GetPerformanceCounter();
			
			//Create entities
			Entity shooter(Vector2f(shooter_pos_x, shooter_pos_y), shooter_tex, shooter_size);
			for (int i = 1; i < asteroid_num; i++)
			{	
				float rand_x = (float)(rand() % (screen_width - asteroid_size - asteroid_size + 1));
				float rand_y = (float)(rand() % (screen_height - asteroid_size - asteroid_size + 1));
				Entity asteroid(Vector2f(rand_x, rand_y), asteroid_tex, asteroid_size);
				asteroids.push_back(asteroid);
			}
			/*Entity asteroid(Vector2f(rand_x, rand_y), asteroid_tex, asteroid_size);*/

			Input input = {};
			while (running)
			{	

				//reset inputs;
				for (int i = 0; i < BUTTON_COUNT; i++)
				{
					input.states[i].is_down = false;
				}

				//Taking inputs 
				while (SDL_PollEvent(&e) != 0)
				{	
					
					//Users requests quit 
					if (e.type == SDL_QUIT)
					{
						running = false;
					}
					else if (e.type == SDL_MOUSEMOTION)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);
						input.Mouse2f.x = x ; 
						input.Mouse2f.y = y ;
					}
					else if(e.type == SDL_MOUSEBUTTONDOWN)
					{
						input.states[MOUSE_DOWN].is_down = true;
						Mix_PlayChannel(-1, launch_sound, 0);
					}
				}
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_UP])
				{
					input.states[BUTTON_UP].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_DOWN])
				{
					input.states[BUTTON_DOWN].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_LEFT])
				{
					input.states[BUTTON_LEFT].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					input.states[BUTTON_RIGHT].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_W])
				{
					input.states[BUTTON_W].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_A])
				{
					input.states[BUTTON_A].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_S])
				{
					input.states[BUTTON_S].is_down = true;
				}
				else if (currentKeyStates[SDL_SCANCODE_D])
				{
					input.states[BUTTON_D].is_down = true;
				}

				//Simulate game 
				
				render_window.clear();
				game.simulate_shooter(shooter , &input, delta_time , render_window, shooter_tex); 
				game.simulate_bullet(shooter , &input , delta_time , render_window, bullet_tex);
				game.simulate_asteroid(asteroids);
				render_window.render(shooter);
				for (Entity& asteroid : asteroids)
				{
					render_window.render(asteroid);
				}
				render_window.update();
				Uint64 frame_end_time = SDL_GetPerformanceCounter();
				delta_time = ((float)frame_end_time - frame_begin_time) / SDL_GetPerformanceFrequency();
				float fps = utils.clamp_frame(1.0f / delta_time);
				/*std::cout << fps << "FPS" << std::endl;*/
				frame_begin_time = frame_end_time;
			}

			render_window.close();
		}
		
	}

	return 0;
}
	


