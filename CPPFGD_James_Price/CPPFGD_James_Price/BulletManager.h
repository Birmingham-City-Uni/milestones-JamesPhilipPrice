#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "Target.h"
#include "EnemyAIManager.h"
#include "LevelSystem.h"
#include "Keys.h"

#define PI 3.14159265
#define PLAYERID 0
#define ENEMYID 1

class BulletManager {
public:
	BulletManager(SDL_Renderer* _renderer, Player* _player, EnemyAIManager* _enemies, LevelSystem* _level) : renderer(_renderer), player(_player), enemyManager(_enemies), levelSystem(_level) {}

	struct Bullet {
		float x, y, rotation, distance;
		int shooterID;
		bool active = false;
	};

	void Init() {
		SDL_Surface* surface = IMG_Load("assets/bullet.png");
		this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
		for (int i = 0; i < enemyManager->GetEnemies().size(); i++) {
			enemyLastShot.push_back(0);
		}
	}

	int GetFirstAvailableBullet() {
		int index = 0;
		for (auto& b : bullets) {
			if (!b.active) return index;
		}
		return -1;
	}

	void ProcessInput(bool _keys[]) {
		if (_keys[MOUSELEFT]) {
			if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS) {
				std::cout << "Shooting!" << std::endl;
				float x = player->GetOriginX();
				float y = player->GetOriginY();
				int i = GetFirstAvailableBullet();
				if (i != -1) {
					bullets[i].x = x;
					bullets[i].y = y;
					bullets[i].rotation = player->GetAngle();
					bullets[i].distance = 0.0f;
					bullets[i].shooterID = PLAYERID;
					bullets[i].active = true;
				}
				lastShot = SDL_GetTicks();
			}
		}
	}

	void ProcessEnemies() {
		int index = 0;
		for (auto& i : enemyManager->GetEnemies()) {
			if (enemyManager->GetEnemyFiring(index) && SDL_GetTicks() - enemyLastShot[index] > SHOOT_TIMER_MS) {
				float x = i->GetOriginX();
				float y = i->GetOriginY();
				int ind = GetFirstAvailableBullet();
				if (ind != -1) {
					bullets[ind].x = x;
					bullets[ind].y = y;
					bullets[ind].rotation = i->GetAngle();
					bullets[ind].distance = 0.0f;
					bullets[ind].shooterID = ENEMYID;
					bullets[ind].active = true;
				}
				enemyLastShot[index] = SDL_GetTicks();
			}
			index++;
		}
	}

	int Update() {
		//Process the enemy shooting
		ProcessEnemies();
		int scoreVal = 0;
		for (auto& b : bullets) {
			if (b.active) {
				b.x += sin(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
				b.y -= cos(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
				b.distance += BULLET_VELOCITY;

				SDL_Rect bulletRect = { b.x, b.y, 10, 10 };
				SDL_Rect nullRect;
				//Check the player for a bullet collision if the bullet was not sent by the player
				if (b.shooterID != PLAYERID) {
					if (SDL_IntersectRect(&bulletRect, player->GetEntityRect(), &nullRect)) {
						player->DamagePlayer(10);
						std::cout << "The player was shot!" << std::endl;
						b.distance = 1000;
					}
				}
				//Check all of the enemies
				for (auto& i : enemyManager->GetEnemies()) {
					if (b.shooterID != ENEMYID && SDL_IntersectRect(&bulletRect, i->GetEntityRect(), &nullRect)) {
						//Deals damage to the enemy and checks if it is dead
						if (!(i->TakeDamage(10))) {
							i->UnlockChest();
							std::cout << "The enemy has died and their inventory is now unlocked" << std::endl;
							enemyManager->CreateNewEnemy();
						}
						scoreVal++;
						b.distance = 1000;
						break;
					}
					if (b.distance >= 1000) {
						continue;
					}
				}

				//Checks the current tiles that the bullets are on to see if they are solid tiles
				//Solid tiles that destroy bullets will return true
				if (levelSystem->CheckTileSolidity(b.x, b.y)) {
					b.distance = 1000;
					std::cout << "Bullet collided with a solid tile and needs to be destroyed!" << std::endl;
				}
			}
			if (b.distance >= 1000) {
				b.active = false;
			}
		}

		return scoreVal;
	}

	void Draw() {
		SDL_Point center = { 5, 5 };
		for (auto& b : bullets) {
			if (b.active) {
				SDL_Rect dest = { b.x, b.y, 10, 10 };
				SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
			}
		}
	}

	void Clean() {
		SDL_DestroyTexture(this->bulletTexture);
	}


private:
	SDL_Renderer* renderer;
	SDL_Texture* bulletTexture;
	Player* player;
	EnemyAIManager* enemyManager;
	LevelSystem* levelSystem;
	Bullet bullets[100];
	const int SHOOT_TIMER_MS = 300;
	const int BULLET_VELOCITY = 1;
	unsigned int lastShot = 0;
	std::vector<unsigned int> enemyLastShot;
};