#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"


class RenderWindow
{
public:

	SDL_Renderer* getRenderer();
	RenderWindow(const char* title, int width, int height);
	void render(Entity& entity);
	void close();
	void clear();
	void update();
	SDL_Texture* loadTexture(const char* path);

	

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
};