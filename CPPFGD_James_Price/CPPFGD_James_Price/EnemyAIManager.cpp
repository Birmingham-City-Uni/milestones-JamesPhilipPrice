#include "EnemyAIManager.h"

EnemyAIManager::EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer)
{
	enemies.push_back(new Container(50, 50, "assets/enemy.png", _renderer, true, true, 100));
}

EnemyAIManager::~EnemyAIManager()
{
}

void EnemyAIManager::Update()
{
}

void EnemyAIManager::Draw()
{
	for (auto& i : enemies) {
		i->Draw();
	}
}
