#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Entity.hpp"
#include "Bullet.hpp"


class RenderWindow
{
public:

	SDL_Renderer* getRenderer();
	RenderWindow(const char* title, int width, int height);
	void render(Entity& entity);
	void render_bullet(Bullet& bullet);
	void close();
	void clear();
	void update();
	SDL_Texture* loadTexture(const char* path);
	Mix_Chunk* loadAudio(const char* path);


	

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
};