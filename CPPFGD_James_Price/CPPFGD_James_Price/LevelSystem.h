#pragma once
#include <map>
#include <SDL.h>
#include <SDL_image.h>

#define TILESIZE 32;

/*
* Sumary of int to tile mapping
* 0 - grass
* 1 - tile
* 2 - bush
* 3 - glass
*/

//Definitions for different types of tiles
enum interactability {
	SOLID,
	OPEN,
	WALKABLE_MASKING,
	BREAKABLE_SOLID,
	BREAKABLE_TRANSPARENT
};

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
	SDL_Texture* tile;
	SDL_Texture* bush;
	SDL_Texture* glass_hor;
	SDL_Texture* glass_ver;

	int level[20][25];

	std::map<int, interactability> tileInteraction = {
		{0 , OPEN},
		{1 , SOLID},
		{2 , WALKABLE_MASKING},
		{3 , BREAKABLE_TRANSPARENT}
	};
};