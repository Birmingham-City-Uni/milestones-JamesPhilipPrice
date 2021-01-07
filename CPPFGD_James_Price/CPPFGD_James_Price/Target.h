#pragma once
#include "Entity.h"

class Target : public Entity {
public:
	Target(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health, LevelSystem* _level);
	~Target();
};