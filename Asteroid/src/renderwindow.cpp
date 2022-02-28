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
void RenderWindow::clear()
{
	SDL_RenderClear(renderer); //Clear screen
}

void RenderWindow::render(Entity& entity) //Render texture to screen
{	

	SDL_Rect src;
	src.x = 0; 
	src.y = 0; 
	src.w = 8;
	src.h = 8;

	SDL_Rect dest;
	dest.x = entity.currentFrame.x;
	dest.y = entity.currentFrame.y;
	dest.w = entity.size;
	dest.h = entity.size;

	SDL_RenderCopyEx(renderer, entity.tex, NULL, &dest, entity.rotation_angle, NULL ,  SDL_FLIP_NONE);
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

//void RenderWindow::draw_rect(int x, int y, int half_size_x, int half_size_y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
//{	
//	SDL_Rect fillRect = { x - half_size_x , y - half_size_y, x + half_size_x , y + half_size_y };
//	SDL_SetRenderDrawColor(renderer, r , g ,b ,a );
//	SDL_RenderFillRect(renderer, &fillRect);
//
//}
