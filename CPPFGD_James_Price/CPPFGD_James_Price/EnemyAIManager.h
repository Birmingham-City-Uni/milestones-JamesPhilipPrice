#pragma once
#include "Container.h"
#include "Player.h"
#include "RayCasting.h"
#include "LevelSystem.h"
#include <vector>
#include <cmath>
#include <map>

#define PI 3.14159265

#define WALKSPEED 0.05
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
	bool GetEnemyFiring(int _index);

	void Update(bool _keysInp[]);
	void Draw();

private:
	//Checking player visibility
	int tileRadiusForCheck = 10;
	bool CheckVisibilityToPlayer(Container* _enemy);
	const int FOV = 90;
	//RayCasting collision detection 
	Ray* visibilityRay;
	RayCastingTools* rayTools;
	vector<Container*> enemies;
	LevelSystem* level;
	Player* player;
	EnemyState* enemyStates;
	SDL_Point* tempPos;
};