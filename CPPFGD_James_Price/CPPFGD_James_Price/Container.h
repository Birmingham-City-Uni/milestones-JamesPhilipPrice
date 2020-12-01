#pragma once
#include<iostream>
#include "Entity.h"
#include "Player.h"
#include "Keys.h"

enum LootType {
	Empty = 0,
	Food,
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
	void CloseChest();
	void UnlockChest();
	void CheckForOpenCondition(Player* _player, bool _keysInp[]);
	void CheckForCloseCondition(Player* _player);

private:
	bool unlocked = true;
	bool open;
	Player* player;
};