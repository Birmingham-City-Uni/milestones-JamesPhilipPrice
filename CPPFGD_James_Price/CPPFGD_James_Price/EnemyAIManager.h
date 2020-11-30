#pragma once
#include "Container.h"
#include <vector>

using namespace std;

class EnemyAIManager {
public:
	EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer);
	~EnemyAIManager();

	void Update();
	void Draw();

private:
	 vector<Container*> enemies;
};