#pragma once
#include "RayCasting.h"
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#define PI 3.14159265

#define CENTEROFFSET 16;

/*
* Sumary of int to tile mapping
* 0 - grass
* 1 - tile
* 2 - bush
* 3 - glass
* 4 - wood
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
	
	int GetTileFromXY(int _x, int _y);
	bool CheckTileSolidity(int _x, int _y);

	std::vector <int> CheckForSolidTileProximity(SDL_Point* _position, int _triggerRadius, int _originAngle, int _fov);

	void LoadMap(int _levelArray[20][40]);
	void CreateEdgeMap();
	void CreateCollisionEdgeMap();
	void DrawMap();

	std::vector<Edge> edgePool;
	std::vector<Edge> collsionEdgePool;

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;

	std::vector<int> selectedTiles;

	SDL_Texture* grass;
	SDL_Texture* tile;
	SDL_Texture* bush;
	SDL_Texture* glass_hor;
	SDL_Texture* glass_ver;
	SDL_Texture* wood;

	int level[20][40];
	int levelEdgeRegister[20][40][4];
	int levelCollisionEdgeRegister[20][40][4];
	int xLength = 40;
	int yLength = 20;

	const int TILESIZE = 32;

	std::map<int, interactability> tileInteraction = {
		{0 , OPEN},
		{1 , SOLID},
		{2 , WALKABLE_MASKING},
		{3 , BREAKABLE_TRANSPARENT},
		{4 , BREAKABLE_TRANSPARENT},
		{5 , OPEN}
	};
};