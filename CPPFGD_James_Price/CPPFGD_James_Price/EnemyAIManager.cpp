#include "EnemyAIManager.h"

EnemyAIManager::EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player, LevelSystem* _level)
{
	//Player is holding a reference to the player object and the enemyStates holds the current behaviour state of all enemies in the manager
	this->player = _player;
	this->level = _level;
	this->enemyStates = new EnemyState[_enemyCount];
	this->visibilityRay = new Ray;
	this->rayTools = new RayCastingTools();

	//PreCalulating distance variables
	tileRadiusForCheck *= 32;
	tileRadiusForCheck = tileRadiusForCheck * tileRadiusForCheck; //So I don't need to square root stuff
	tempPos = new SDL_Point();

	//Create as many enemies as needed and set each of their states
	for (int i = 0; i < _enemyCount; i++) {
		enemies.push_back(new Container(50, 50, "assets/enemy.png", _renderer, true, true, 100));
		this->enemyStates[i] = STATIONARY;
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

bool EnemyAIManager::GetEnemyFiring(int _index)
{
	if (enemyStates[_index] == CHASE) return true;
	return false;
}

void EnemyAIManager::Update(bool _keysInp[])
{
	//Run through each enemy and if they are alive make them do living people things, if not do not living people things
	int stateIndex = 0;
	for (auto& i : enemies) {
		if (i->GetLifeState()) {
			//Checks what state the enemy is in and act accordingly
			if (CheckVisibilityToPlayer(i)) {
				//The Enemy can see the player
				enemyStates[stateIndex] = CHASE;
			}
			else {
				//The enemy cannot see the player
				enemyStates[stateIndex] = STATIONARY;
			}
			int deltaX;
			int deltaY;
			float newAngle;
			float movement[2];
			switch (enemyStates[stateIndex]) {
			case STATIONARY:
				i->SetAngle(i->GetAngle() + 0.01);
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

bool EnemyAIManager::CheckVisibilityToPlayer(Container* _enemy)
{
	//Check if the player is close enough to even bother checking
	int disX = _enemy->GetOriginX() - player->GetOriginX();
	int disY = _enemy->GetOriginY() - player->GetOriginY();
	int disMag = (disX * disX) + (disY * disY);
	if (disMag < tileRadiusForCheck) {
		//We need to check for visibility, first check if the player is in the field of view
		float angleToPlayer = ((atan2(disY, disX) * (180 / PI)) - 90)-_enemy->GetAngle(); //In degrees
		if (angleToPlayer < -180) {
			angleToPlayer += 360;
		}
		if (angleToPlayer >= -(FOV / 2) && angleToPlayer <= (FOV / 2)) {
			//Player is in the FOV we need to check for any obstructions
			visibilityRay->edge.start.x = _enemy->GetOriginX();
			visibilityRay->edge.start.y = _enemy->GetOriginY();
			visibilityRay->edge.end.x = player->GetOriginX();
			visibilityRay->edge.end.y = player->GetOriginY();
			visibilityRay->intersected = false;

			for (auto& i : level->edgePool) {
				bool result = rayTools->CheckIntersection(&visibilityRay->edge, &i);
				if (result) {
					visibilityRay->intersected = true;
					break;
				}
			}
			return !visibilityRay->intersected;
		}
		else {
			//The player is not in the field of view
			return false;
		}
	}
	else {
		//The player is outside of the vision range
		return false;
	}
	return false;
}
