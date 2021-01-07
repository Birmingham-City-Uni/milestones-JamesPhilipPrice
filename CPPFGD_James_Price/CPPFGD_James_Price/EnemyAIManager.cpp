#include "EnemyAIManager.h"

EnemyAIManager::EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player, LevelSystem* _level, UIManager* _ui)
{
	//Player is holding a reference to the player object and the enemyStates holds the current behaviour state of all enemies in the manager
	this->player = _player;
	this->level = _level;
	this->ui = _ui;
	this->visibilityRay = new Ray;
	this->patrolVisibilityRay = new Ray;
	this->rayTools = new RayCastingTools();
	this->renderer = _renderer;

	SDL_Surface* temp = IMG_Load("assets/visionCone.png");
	viewCone = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);

	//PreCalulating distance variables
	tileRadiusForCheck *= 32;
	tileRadiusForCheck = tileRadiusForCheck * tileRadiusForCheck; //So I don't need to square root stuff
	tempPos = new SDL_Point();

	//Create as many enemies as needed and set each of their states
	for (int i = 0; i < _enemyCount; i++) {
		SDL_Point temp;
		FindValidSpawnPoint(&temp);
		enemies.push_back(new Container(temp.x, temp.y, "assets/enemy.png", _renderer, true, true, 100, this->level));
		enemyPatrolLocations.push_back(new SDL_Point());
		SetOpenPathPos(&temp, enemyPatrolLocations[enemyPatrolLocations.size()-1]);
		this->enemyStates[i] = PATROL;
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
	if (enemies[_index]->GetLifeState() && enemyStates[_index] == CHASE) return true;
	return false;
}

void EnemyAIManager::FindValidSpawnPoint(SDL_Point* _point)
{
	SetRandomPos(_point);
	while (level->CheckTileSolidity(_point->x, _point->y)) {
		SetRandomPos(_point);
	}
}

void EnemyAIManager::SetOpenPathPos(SDL_Point* _start, SDL_Point* _target)
{
	patrolVisibilityRay->edge.start = *_start;
	patrolVisibilityRay->intersected = false;
	for (int i = 0; i < 10; i++) {
		SetRandomPos(&patrolVisibilityRay->edge.end);
		for (auto& j : level->collsionEdgePool) {
			bool result = rayTools->CheckIntersection(&patrolVisibilityRay->edge, &j);
			if (result) {
				patrolVisibilityRay->intersected = true;
				break;
			}
		}
		if (!patrolVisibilityRay->intersected) {
			break;
		}
	}
	_target->x = patrolVisibilityRay->edge.end.x;
	_target->y = patrolVisibilityRay->edge.end.y;
}

void EnemyAIManager::SetRandomPos(SDL_Point* _point)
{
	_point->x = rand() % (MAXXVAL + 1);
	_point->y = rand() % (MAXYVAL + 1);
}

void EnemyAIManager::CreateNewEnemy()
{
	SDL_Point temp;
	FindValidSpawnPoint(&temp);
	enemies.push_back(new Container(temp.x, temp.y, "assets/enemy.png", this->renderer, true, true, 100, this->level));
	enemyPatrolLocations.push_back(new SDL_Point());
	SetOpenPathPos(&temp, enemyPatrolLocations[enemyPatrolLocations.size() - 1]);
	this->enemyStates[enemies.size() - 1] = PATROL;
	cout << "Created new enemy. Number of enemy entities in world: " << enemies.size() << endl;
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
				enemyStates[stateIndex] = PATROL;
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
			case PATROL:
				deltaX = i->GetOriginX() - enemyPatrolLocations[stateIndex]->x;
				deltaY = i->GetOriginY() - enemyPatrolLocations[stateIndex]->y;
				if ((deltaX * deltaX) + (deltaY * deltaY) < patrolPointReachedTrigger) {
					//Change the patrol point target because the ai reached the target
					SDL_Point temp = { i->GetOriginX(), i->GetOriginY() };
					SetOpenPathPos(&temp, enemyPatrolLocations[stateIndex]);
					deltaX = i->GetOriginX() - enemyPatrolLocations[stateIndex]->x;
					deltaY = i->GetOriginY() - enemyPatrolLocations[stateIndex]->y;
				}
				newAngle = (atan2(deltaY, deltaX) * (180 / PI)) - 90;
				i->SetAngle(newAngle);

				//Move the ai
				movement[0] = sin(newAngle * PI / 180.0f) * WALKSPEED;
				movement[1] = -cos(newAngle * PI / 180.0f) * WALKSPEED;
				i->Move(movement);
				break;
			default:
				cout << "Is there somthing wrong with the enemy??" << endl;
				break;
			}
		}
		else {
			if (i->CheckForOpenCondition(this->player, _keysInp)) {
				ui->SetDrawPlaceHolderVal(false);
			}
			
			if (i->CheckForCloseCondition(this->player)) {
				ui->SetDrawPlaceHolderVal(true);
			}
		}
		stateIndex++;
	}
}

void EnemyAIManager::Draw()
{
	for (auto& i : enemies) {
		//Check if the enemy can be seen
		int disX = player->GetOriginX() - i->GetOriginX();
		int disY = player->GetOriginY() - i->GetOriginY();
		int disMag = (disX * disX) + (disY * disY);
		if (disMag < tileRadiusForCheck*2) {
			//We need to check for visibility, first check if the enemy is in the field of view
			float angleToEnemy = ((atan2(disY, disX) * (180 / PI)) - 90) - player->GetAngle(); //In degrees
			if (angleToEnemy < -180) {
				angleToEnemy += 360;
			}
			if (angleToEnemy >= -(FOV) && angleToEnemy <= (FOV)) {
				//The ai is in the player's fov need to check for obstruction
				visibilityRay->edge.start.x = player->GetOriginX();
				visibilityRay->edge.start.y = player->GetOriginY();
				visibilityRay->edge.end.x = i->GetOriginX();
				visibilityRay->edge.end.y = i->GetOriginY();
				visibilityRay->intersected = false;

				for (auto& j : level->edgePool) {
					bool result = rayTools->CheckIntersection(&visibilityRay->edge, &j);
					if (result) {
						visibilityRay->intersected = true;
						break;
					}
				}
				if (!visibilityRay->intersected) {
					//Draw the enemy's vision cone
					dest.x = i->GetOriginX() - src.w / 2;
					dest.y = i->GetOriginY() - src.h / 2;
					SDL_RenderCopyEx(this->renderer, this->viewCone, &src, &dest, i->GetAngle(), NULL, SDL_FLIP_NONE);
					//Draw the enemy on top
					i->Draw();
				}
			}
		}
	}
}

void EnemyAIManager::DrawInvs()
{
	for (auto& i : enemies) {
		i->DrawInv();
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
