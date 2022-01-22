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

	void draw_rect(int x, int y, int half_size_x, int half_size_y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
};