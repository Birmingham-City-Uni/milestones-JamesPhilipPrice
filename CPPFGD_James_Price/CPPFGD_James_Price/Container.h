#pragma once
#include<iostream>
#include "Player.h"
#include "Keys.h"

class Container : public Entity{
public:
	Container(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health, LevelSystem* _level);
	~Container();

	LootType inventory[5][6];

	void OpenChest();
	void CloseChest();
	void UnlockChest();
	bool CheckForOpenCondition(Player* _player, bool _keysInp[]);
	bool CheckForCloseCondition(Player* _player);
	bool IsChestOpen();
	bool TryTakeNextItem();

	int GetInvetorySlotItem(int _x, int _y);

	void DrawInv();

private:
	int lastItemTake = 0;
	int itemTakeWaitTicks = 500;
	bool unlocked = true;
	bool open;
	SDL_Renderer* renderer;
	//Inventory panel
	SDL_Texture* items;
	SDL_Point inventoryOffset = { 500, 640 };
	SDL_Rect itemSrc = { 0, 0, 16, 16 };
	SDL_Rect itemDest = { 0, 0, 16, 16 };
};