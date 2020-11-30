#pragma once
#include "Entity.h"

enum LootType {
	Food = 0,
	Water,
	Bolts,
	GunParts
};

class Container : public Entity{
public:
	Container(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health);
	~Container();

	LootType inventory[5][6];

	void OpenChest();
	void UnlockChest();

private:
	bool unlocked;
	bool open;
};