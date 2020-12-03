#pragma once
#include "Container.h"
#include "Player.h"
#include <vector>

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