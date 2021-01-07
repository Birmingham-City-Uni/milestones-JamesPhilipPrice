#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "Keys.h"

class UIManager {
public:
	UIManager(SDL_Renderer* _renderer);
	~UIManager();

	void UpdateHealthBar(float _percentage);
	void UpdateStaminaBar(float _percentage);

	void SetDrawPlaceHolderVal(bool _val) {
		drawInv = _val;
	}
	bool GetDrawPlaceHolderVal() {
		return drawInv;
	}

	void Draw();

private:
	SDL_Renderer* renderer;

	SDL_Texture* uiBackground;
	SDL_Rect backgroundSrc = {0, 0, 1280, 80};
	SDL_Rect backgroundDest = {0, 640, 1280, 80};

	//Inventory panel
	SDL_Texture* items;
	bool drawInv = true;
	SDL_Point inventoryOffset = {500, 640};
	SDL_Rect itemSrc = { 0, 0, 16, 16 };
	SDL_Rect itemDest = {0, 0, 16, 16};

	//The health and staminma bar
	SDL_Texture* backing;
	SDL_Texture* health;
	SDL_Texture* stamina;

	SDL_Rect src = {0, 0, 32, 32};

	int maxBarLength = 128;
	SDL_Rect healthBacking = {0, 670, maxBarLength, 8};
	SDL_Rect healthBar = { 0, 670, maxBarLength, 8 };
	SDL_Rect staminaBacking = { 0, 690, maxBarLength, 8 };
	SDL_Rect staminaBar = { 0, 690, maxBarLength, 8 };
};