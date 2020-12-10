#include "EnemyAIManager.h"

EnemyAIManager::EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player)
{
	this->player = _player;
	for (int i = 0; i < _enemyCount; i++) {
		enemies.push_back(new Container(50, 50, "assets/enemy.png", _renderer, true, true, 100));
	}
	for (auto& i : enemies) {
		i->SetLifeState(true);
	}
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
	//Run through each enemy and if they are alive make them do living people things, if not do not living people things
	for (auto& i : enemies) {
		if (i->GetLifeState()) {
			//Basic chase behaviour
			//Set the angle of the enemy based on the direction to player
			int deltaX = i->GetOriginX() - player->GetOriginX();
			int deltaY = i->GetOriginY() - player->GetOriginY();
			float newAngle = (atan2(deltaY, deltaX) * (180 / PI)) - 90;
			i->SetAngle(newAngle);

			//Move forwards in the direction that the enemy is looking
			float movement[2];
			movement[0] = sin(newAngle * PI / 180.0f) * WALKSPEED;
			movement[1] = -cos(newAngle * PI / 180.0f) * WALKSPEED;
			i->Move(movement);
		}
		else {
			//When the enemy is dead the player can mess with their inventory, these are the method calls to check for it
			i->CheckForOpenCondition(this->player, _keysInp);
			i->CheckForCloseCondition(this->player);
		}
	}
}

void EnemyAIManager::Draw()
{
	for (auto& i : enemies) {
		i->Draw();
	}
}
