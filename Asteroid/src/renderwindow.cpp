#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "renderwindow.hpp"
#include "Entity.hpp"





RenderWindow::RenderWindow(const char* title, int width, int height)
	:window(NULL), renderer(NULL) , texture(NULL)
{	
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	SDL_GetWindowSize(window, &width, &height);
	if (window == NULL)
	{
		printf("Couldn't create window , Error : %s\n", SDL_GetError());
	}
	else
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	
}


SDL_Texture* RenderWindow::loadTexture(const char* path)
{	
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
		{
			printf("Unable to laod texture .... %s \n", path);
		}
		SDL_FreeSurface(loadedSurface);
		
	}
	return texture;
	
}

Mix_Chunk* RenderWindow::loadAudio(const char* path)
{
	Mix_Chunk* audio = Mix_LoadWAV(path);
	if (audio == NULL)
	{
		printf("Unable to load audio ... %s \n", path);
	}
	return audio;
}
void RenderWindow::clear()
{
	SDL_RenderClear(renderer); //Clear screen
}

void RenderWindow::render(Entity& entity) //Render texture to screen
{	


	SDL_Rect dest;
	dest.x = entity.pos.x;
	dest.y = entity.pos.y;
	dest.w = entity.size;
	dest.h = entity.size;

	SDL_RenderCopyEx(renderer, entity.tex, NULL, &dest, entity.rotation_angle, NULL ,  SDL_FLIP_NONE);
}

void RenderWindow::render_bullet(Bullet& bullet)
{
	SDL_Rect dest;
	dest.x = bullet.pos.x;
	dest.y = bullet.pos.y;
	dest.w = 8;
	dest.h = 8; 

	SDL_RenderCopy(renderer, bullet.tex, NULL, &dest);
}

void RenderWindow::update() //Update the screen
{	
	SDL_RenderPresent(renderer);
}
void RenderWindow::close()
{	
	SDL_DestroyTexture(texture);
	texture = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;
	

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}


