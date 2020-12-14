#include "LevelSystem.h"

int levelData[20][25] = { 
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

LevelSystem::LevelSystem(SDL_Renderer* _renderer) {
	this->renderer = _renderer;
	SDL_Surface* tempSurface = IMG_Load("assets/grass.png");
	grass = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = IMG_Load("assets/tile.png");
	tile = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = IMG_Load("assets/bush.png");
	bush = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = IMG_Load("assets/glass_hor.png");
	glass_hor = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = IMG_Load("assets/glass_ver.png");
	glass_ver = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	src.x = src.y = 0;
	src.w = src.h = dest.w = dest.h = TILESIZE;
	dest.x = dest.y = 0;
	LoadMap(levelData);
}

void LevelSystem::LoadMap(int _levelArray[20][25])
{
	for (int row = 0; row < 20; row++) {
		for (int collumn = 0; collumn < 25; collumn++) {
			level[row][collumn] = levelData[row][collumn];
		}
	}
}

void LevelSystem::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 20; row++) {
		for (int collumn = 0; collumn < 25; collumn++) {
			type = level[row][collumn];


			dest.x = collumn * TILESIZE;
			dest.y = row * TILESIZE;

			//Checking which type of tile needs to be used then rendering it
			switch (type) {
			case 0:
				SDL_RenderCopy(this->renderer, this->grass, &src, &dest);
				break;
			case 1:
				SDL_RenderCopy(this->renderer, this->tile, &src, &dest);
				break;
			case 2:
				SDL_RenderCopy(this->renderer, this->bush, &src, &dest);
				break;
			case 3:
				SDL_RenderCopy(this->renderer, this->glass_hor, &src, &dest);
				break;
			case 4:
				SDL_RenderCopy(this->renderer, this->glass_ver, &src, &dest);
				break;
			default:
				break;
			}
		}
	}
}

int LevelSystem::GetTileFromXY(int _x, int _y) {
	int xIndex = (int)_x / TILESIZE;
	int yIndex = (int)_y / TILESIZE;
	if (xIndex >= xLength || yIndex >= yLength) {
		std::cout << "Bullet out of map range" << std::endl;
		//returns the default solid tile type
		return 1;
	}
	return levelData[yIndex][xIndex];
}

bool LevelSystem::CheckTileSolidity(int _x, int _y)
{
	int tileNumber = GetTileFromXY(_x, _y);
	switch (tileInteraction[tileNumber]) {
	case SOLID:
		return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}
