#include "EnemyAIManager.h"

EnemyAIManager::EnemyAIManager(int _enemyCount, SDL_Renderer* _renderer, Player* _player, LevelSystem* _level)
{
	//Player is holding a reference to the player object and the enemyStates holds the current behaviour state of all enemies in the manager
	this->player = _player;
	this->level = _level;
	this->enemyStates = new EnemyState[_enemyCount];
	this->visibilityRay = new Ray;
	this->checkingEdge = new Edge;
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

void EnemyAIManager::Update(bool _keysInp[])
{
	//Run through each enemy and if they are alive make them do living people things, if not do not living people things
	int stateIndex = 0;
	for (auto& i : enemies) {
		if (i->GetLifeState()) {
			//Checks what state the enemy is in and act accordingly
			if (CheckVisibilityToPlayer(i)) {
				//The Enemy can see the player
				cout << "The player can be seen!" << endl;
			}
			else {
				//The enemy cannot see the player
				cout << "The player can NOT be seen!" << endl;
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
			//The player is in the field of view, we need to check for obstructions
			tempPos->x = _enemy->GetOriginX();
			tempPos->y = _enemy->GetOriginY();
			vector<int> selectedTiles =  level->CheckForSolidTileProximity(tempPos, tileRadiusForCheck, _enemy->GetAngle(), FOV);
			//Cast a ray to the player
			visibilityRay->edge.start = *tempPos;
			visibilityRay->edge.end.x = player->GetOriginX();
			visibilityRay->edge.end.y = player->GetOriginY();
			visibilityRay->intersected = false;
			//Loop through all of the selected tiles
			cout << "Number of obscuring tiles: " << selectedTiles.size() << endl;
			for (int i = 0; i < selectedTiles.size(); i++) {
				//Get the top left corner first
				int x = selectedTiles[i] % 25;
				int y = floor(selectedTiles[i] / 25);
				x *= TILESIZE;
				y *= TILESIZE;
				//Check top edge
				checkingEdge->start.x = x;
				checkingEdge->start.y = y;
				checkingEdge->end.x = x+TILESIZE;
				checkingEdge->end.y = y;
				visibilityRay->intersected =  rayTools->CheckIntersection(&visibilityRay->edge, checkingEdge);
				if (visibilityRay->intersected) {
					break;
				}
				//Check bottom edge
				checkingEdge->start.x = x;
				checkingEdge->start.y = y+TILESIZE;
				checkingEdge->end.x = x + TILESIZE;
				checkingEdge->end.y = y + TILESIZE;
				visibilityRay->intersected = rayTools->CheckIntersection(&visibilityRay->edge, checkingEdge);
				if (visibilityRay->intersected) {
					break;
				}
				//Check left edge
				checkingEdge->start.x = x;
				checkingEdge->start.y = y;
				checkingEdge->end.x = x;
				checkingEdge->end.y = y + TILESIZE;
				visibilityRay->intersected = rayTools->CheckIntersection(&visibilityRay->edge, checkingEdge);
				if (visibilityRay->intersected) {
					break;
				}
				//Check right edge
				checkingEdge->start.x = x + TILESIZE;
				checkingEdge->start.y = y;
				checkingEdge->end.x = x + TILESIZE;
				checkingEdge->end.y = y + TILESIZE;
				visibilityRay->intersected = rayTools->CheckIntersection(&visibilityRay->edge, checkingEdge);
				if (visibilityRay->intersected) {
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
