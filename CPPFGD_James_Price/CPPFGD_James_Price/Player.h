#pragma once
#include "Entity.h"
#define WALKSPEED 1;
#define RUNSPEED 3;

class Player : public Entity {
public:
	Player(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health);
	~Player();

	void ProcessInput(bool _keys[]);
};
