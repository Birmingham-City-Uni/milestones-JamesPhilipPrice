#include "LevelSystem.h"

int levelData[20][25] = { 
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
	CreateEdgeMap();
}

void LevelSystem::CreateEdgeMap() {
	for (int i = 0; i < yLength; i++) {
		for (int j = 0; j < xLength; j++) {
			//Check if the tile is solid or masking
			if (tileInteraction[level[i][j]] == SOLID || tileInteraction[level[i][j]] == WALKABLE_MASKING) {
				//The tile is able to obscure vision
				//Check tile north
				if (i > 0 && tileInteraction[level[i-1][j]] == SOLID || tileInteraction[level[i-1][j]] == WALKABLE_MASKING) {
					//There is a tile above so no need to do anything
				}
				else {
					//There needs to be an edge
					if (j > 0 && levelEdgeRegister[i][j - 1][0] != NULL) {
						//There is a tile to the left with a north edge we can use
						edgePool[levelEdgeRegister[i][j - 1][0]].end.x = j * TILESIZE + TILESIZE;
						levelEdgeRegister[i][j][0] = levelEdgeRegister[i][j - 1][0];
					}
					else {
						//There isn't a tile to the left with a north edge, we need to make a new one
						Edge temp;
						temp.start.x = j * TILESIZE;
						temp.start.y = i * TILESIZE;
						temp.end = temp.start;
						temp.end.x += TILESIZE;
						edgePool.push_back(temp);
						levelEdgeRegister[i][j][0] = (edgePool.size() - 1);
					}
				}

				//Check tile west
				if (j > 0 && tileInteraction[level[i][j - 1]] == SOLID || tileInteraction[level[i][j - 1]] == WALKABLE_MASKING) {
					//There is a tile to the west so there is no need for an edge
				}
				else {
					//There needs to be a western edge
					if (i > 0 && levelEdgeRegister[i - 1][j][1] != NULL) {
						//There is a tile above with a western edge that we can use
						edgePool[levelEdgeRegister[i - 1][j][1]].end.y = i * TILESIZE + TILESIZE;
						levelEdgeRegister[i][j][1] = levelEdgeRegister[i - 1][j][1];
					}
					else {
						Edge temp;
						temp.start.x = j * TILESIZE;
						temp.start.y = i * TILESIZE;
						temp.end = temp.start;
						temp.end.y += TILESIZE;
						edgePool.push_back(temp);
						levelEdgeRegister[i][j][1] = (edgePool.size() - 1);
					}
				}

				//Check tile east
				if (j < xLength && tileInteraction[level[i][j + 1]] == SOLID || tileInteraction[level[i][j + 1]] == WALKABLE_MASKING) {
					//There is a tile to the east so there is no need for an edge
				}
				else {
					//There needs to be a eastern edge
					if (i > 0 && levelEdgeRegister[i - 1][j][2] != NULL) {
						//There is a tile above with a western edge that we can use
						edgePool[levelEdgeRegister[i - 1][j][2]].end.y = i * TILESIZE + TILESIZE;
						levelEdgeRegister[i][j][2] = levelEdgeRegister[i - 1][j][2];
					}
					else {
						Edge temp;
						temp.start.x = j * TILESIZE + TILESIZE;
						temp.start.y = i * TILESIZE;
						temp.end = temp.start;
						temp.end.y += TILESIZE;
						edgePool.push_back(temp);
						levelEdgeRegister[i][j][2] = (edgePool.size() - 1);
					}
				}

				//Check tile south
				if (i < yLength && tileInteraction[level[i + 1][j]] == SOLID || tileInteraction[level[i + 1][j]] == WALKABLE_MASKING) {
					//There is a tile to the south so there is no need for an edge;
				}
				else {
					//There needs to be a southern edge
					if (j > 0 && levelEdgeRegister[i][j - 1][3] != NULL) {
						//There is a tile to the left with a north edge we can use
						edgePool[levelEdgeRegister[i][j - 1][3]].end.x = j * TILESIZE + TILESIZE;
						levelEdgeRegister[i][j][3] = levelEdgeRegister[i][j - 1][3];
					}
					else {
						//There isn't a tile to the left with a north edge, we need to make a new one
						Edge temp;
						temp.start.x = j * TILESIZE;
						temp.start.y = i * TILESIZE + TILESIZE;
						temp.end = temp.start;
						temp.end.x += TILESIZE;
						edgePool.push_back(temp);
						levelEdgeRegister[i][j][3] = (edgePool.size() - 1);
					}
				}
			}
		}
	}
	std::cout << "Number of edges created: " << edgePool.size() << std::endl;
	for (auto& i : edgePool) {
		std::cout << "Edge X: " << i.start.x << " Y: " << i.start.y << " to X: " << i.end.x << " Y: " << i.end.y << std::endl;
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

std::vector <int> LevelSystem::CheckForSolidTileProximity(SDL_Point* _position, int _triggerRadius, int _originAngle, int _fov) {
	selectedTiles.clear();
	for (int i = 0; i < yLength; i++) {
		for (int j = 0; j < xLength; j++) {
			//Check if the tile is masking or solid
			if (tileInteraction[levelData[i][j]] == SOLID || tileInteraction[levelData[i][j]] == WALKABLE_MASKING) {
				//The tile can block lines of sight, now check if it in the range of vision, I will use each corner of the of the tile and check them
				//This gets the distance to the center of the tiles
				int tileXCenter = j * TILESIZE + CENTEROFFSET;
				int tileYCenter = i * TILESIZE + CENTEROFFSET;
				int disX = _position->x - tileXCenter;
				int disY = _position->y - tileYCenter;
				if ((disX * disX) + (disY * disY) < _triggerRadius) {
					//The tile is in the range of vision, now check if it is in the field of view
					int angleToTile = ((atan2(disY, disX) * (180 / PI)) - 90) - _originAngle;
					if (angleToTile < -180) {
						angleToTile += 360;
					}
					if (angleToTile >= -(_fov / 2) && angleToTile <= (_fov / 2)) {
						//The tile is in the field of view, add it to the vector
						selectedTiles.push_back((xLength*i)+j);
					}
				}
			}
		}
	}
	return selectedTiles;
}