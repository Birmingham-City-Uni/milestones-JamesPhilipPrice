#pragma once
#include "Container.h"
#include "Player.h"
#include "RayCasting.h"
#include "LevelSystem.h"
#include <vector>
#include <cmath>
#include <map>

#define PI 3.14159265

#define WALKSPEED 0.1
#define RUNSPEED 0.3

#define TILESIZE 32

using namespace std;

enum EnemyState {
	STATIONARY,
	CHASE,
	EVADE
};

class EnemyAIManager {
public:
	EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player, LevelSystem* _level);
	~EnemyAIManager();

	vector<Container*> GetEnemies();

	void Update(bool _keysInp[]);
	void Draw();

private:
	//Checking player visibility
	int tileRadiusForCheck = 10;
	bool CheckVisibilityToPlayer(Container* _enemy);
	const int FOV = 70;
	//RayCasting collision detection 
	Ray* visibilityRay;
	Edge* checkingEdge;
	RayCastingTools* rayTools;
	vector<Container*> enemies;
	LevelSystem* level;
	Player* player;
	EnemyState* enemyStates;
	SDL_Point* tempPos;
};