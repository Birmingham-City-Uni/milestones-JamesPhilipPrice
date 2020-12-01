#include "EnemyAIManager.h"

EnemyAIManager::EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player)
{
	this->player = _player;
	enemies.push_back(new Container(50, 50, "assets/enemy.png", _renderer, true, true, 100));
}

EnemyAIManager::~EnemyAIManager()
{
}

vector<Container*> EnemyAIManager::GetEnemies()
{
	return enemies;
}

void EnemyAIManager::Update(bool _keysInp[])
{
	for (auto& i : enemies) {
		i->CheckForOpenCondition(this->player, _keysInp);
		i->CheckForCloseCondition(this->player);
	}
}

void EnemyAIManager::Draw()
{
	for (auto& i : enemies) {
		i->Draw();
	}
}
