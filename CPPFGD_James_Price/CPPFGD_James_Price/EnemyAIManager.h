#pragma once
#include "Container.h"
#include "Player.h"
#include <vector>

#define PI 3.14159265

#define WALKSPEED 0.1
#define RUNSPEED 0.3

using namespace std;

class EnemyAIManager {
public:
	EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player);
	~EnemyAIManager();

	vector<Container*> GetEnemies();

	void Update(bool _keysInp[]);
	void Draw();

private:
	 vector<Container*> enemies;
	 Player* player;
};