#include "EnemyAIManager.h"

EnemyAIManager::EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player)
{
	//Player is holding a reference to the player object and the enemyStates holds the current behaviour state of all enemies in the manager
	this->player = _player;
	this->enemyStates = new EnemyState[_enemyCount];
	//Create as many enemies as needed and set each of their states
	for (int i = 0; i < _enemyCount; i++) {
		enemies.push_back(new Container(50, 50, "assets/enemy.png", _renderer, true, true, 100));
		this->enemyStates[i] = CHASE;
	}
	for (auto& i : enemies) {
		i->SetLifeState(true);
	}

	//TESTING CODE
	for (int i = 0; i < _enemyCount; i++) {
		cout << "Enemy " << i << " state: " << enemyStates[i] << endl;
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
	int stateIndex = 0;
	for (auto& i : enemies) {
		if (i->GetLifeState()) {
			//Checks what state the enemy is in and act accordingly
			int deltaX;
			int deltaY;
			float newAngle;
			float movement[2];
			switch (enemyStates[stateIndex]) {
			case STATIONARY:
				break;
			case CHASE:
				//Basic chase behaviour
				//Set the angle of the enemy based on the direction to player
				deltaX = i->GetOriginX() - player->GetOriginX();
				deltaY = i->GetOriginY() - player->GetOriginY();
				newAngle = (atan2(deltaY, deltaX) * (180 / PI)) - 90;
				i->SetAngle(newAngle);

				//Move forwards in the direction that the enemy is looking
				movement[0] = sin(newAngle * PI / 180.0f) * WALKSPEED;
				movement[1] = -cos(newAngle * PI / 180.0f) * WALKSPEED;
				i->Move(movement);
				break;
			case EVADE:
				break;
			default:
				cout << "Is there somthing wrong with the enemy??" << endl;
				break;
			}
		}
		else {
			//When the enemy is dead the player can mess with their inventory, these are the method calls to check for it
			i->CheckForOpenCondition(this->player, _keysInp);
			i->CheckForCloseCondition(this->player);
		}
		stateIndex++;
	}
}

void EnemyAIManager::Draw()
{
	for (auto& i : enemies) {
		i->Draw();
	}
}
