#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define TILESIZE 32;

class LevelSystem {
public:
	LevelSystem(SDL_Renderer* _renderer);
	~LevelSystem();

	void LoadMap(int _levelArray[20][25]);
	void DrawMap();

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;

	SDL_Texture* grass;

	int level[20][25];
};