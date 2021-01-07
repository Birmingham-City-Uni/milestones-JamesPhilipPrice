#pragma once
#include "Container.h"
#include "Player.h"
#include "RayCasting.h"
#include "LevelSystem.h"
#include "UIManager.h"
#include <vector>
#include <cmath>
#include <map>

#define PI 3.14159265

#define WALKSPEED 0.05
#define RUNSPEED 0.3

#define TILESIZE 32

#define MAXXVAL 1280
#define MAXYVAL 640

using namespace std;

enum EnemyState {
	STATIONARY,
	CHASE,
	EVADE,
	PATROL
};

class EnemyAIManager {
public:
	EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player, LevelSystem* _level, UIManager* _ui);
	~EnemyAIManager();

	vector<Container*> GetEnemies();
	bool GetEnemyFiring(int _index);

	void FindValidSpawnPoint(SDL_Point* _point);

	void SetOpenPathPos(SDL_Point* _start, SDL_Point* _target);
	void SetRandomPos(SDL_Point* _point);

	void CreateNewEnemy();

	void Update(bool _keysInp[]);
	void Draw();
	void DrawInvs();

private:
	//Updating the UI
	UIManager* ui;
	//Checking player visibility
	int tileRadiusForCheck = 10;
	bool CheckVisibilityToPlayer(Container* _enemy);
	const int FOV = 90;
	//RayCasting collision detection 
	Ray* visibilityRay;
	Ray* patrolVisibilityRay;
	RayCastingTools* rayTools;
	//Stuff for enemies
	vector<SDL_Point*> enemyPatrolLocations;
	int patrolPointReachedTrigger = 4;
	SDL_Renderer* renderer;
	SDL_Texture* viewCone;
	SDL_Rect src = { 0, 0, 256, 256 };
	SDL_Rect dest = { 0, 0, 256, 256 };
	vector<Container*> enemies;
	LevelSystem* level;
	Player* player;
	EnemyState enemyStates[100];
	SDL_Point* tempPos;
};