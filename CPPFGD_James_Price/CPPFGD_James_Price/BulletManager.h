#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "Target.h"
#include "Keys.h"

#define PI 3.14159265

class BulletManager {
public:
	BulletManager(SDL_Renderer* _renderer, Player* _player, Target* _target) : renderer(_renderer), player(_player), target(_target) {}

	struct Bullet {
		float x, y, rotation, distance;
	};

	void Init() {
		SDL_Surface* surface = IMG_Load("assets/bullet.png");
		this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
	}

	void ProcessInput(bool _keys[]) {
		if (_keys[MOUSELEFT]) {
			if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS) {
				std::cout << "Shooting!" << std::endl;
				float x = player->GetOriginX();
				float y = player->GetOriginY();
				bullets.push_back(Bullet{ x, y, player->GetAngle(), 0.0f });
				lastShot = SDL_GetTicks();
			}
		}
	}

	int Update() {
		int scoreVal = 0;
		for (auto& b : bullets) {
			b.x += sin(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
			b.y -= cos(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;

			SDL_Rect bulletRect = {b.x, b.y, 10, 10};
			SDL_Rect nullRect;
<<<<<<< HEAD
			if (SDL_IntersectRect(&bulletRect, target->GetEntityRect(), &nullRect)) {
				std::cout << "Hit the target! We got some points, right Carlo?" << std::endl;
				scoreVal++;
				b.distance = 1000;
=======
			//Check all of the enemies
			for (auto& i : enemyManager->GetEnemies()) {
				if (SDL_IntersectRect(&bulletRect, i->GetEntityRect(), &nullRect)) {
					i->TakeDamage(10);
					scoreVal++;
					b.distance = 1000;
					break;
				}
				if (b.distance >= 1000) {
					continue;
				}
>>>>>>> parent of 0ffb9fb... Merge branch 'Developments'
			}
		}

		auto remove = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){return b.distance >= 1000; });
		bullets.erase(remove, bullets.end());
		return scoreVal;
	}

	void Draw() {
		SDL_Point center = { 5, 5 };
		for (auto& b : bullets) {
			SDL_Rect dest = { b.x, b.y, 10, 10 };
			SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
		}
	}

	void Clean() {
		SDL_DestroyTexture(this->bulletTexture);
	}


private:
	SDL_Renderer* renderer;
	SDL_Texture* bulletTexture;
	Player* player;
	Target* target;
	std::vector<Bullet> bullets;
	const int SHOOT_TIMER_MS = 300;
	const int BULLET_VELOCITY = 1;
	unsigned int lastShot = 0;
};