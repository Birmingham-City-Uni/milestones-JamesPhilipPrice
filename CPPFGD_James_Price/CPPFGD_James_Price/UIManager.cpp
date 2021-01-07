#include "UIManager.h"

UIManager::UIManager(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	SDL_Surface* temp = IMG_Load("assets/backing.png");
	this->backing = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("assets/health.png");
	this->health = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("assets/stamina.png");
	this->stamina = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("assets/Items.png");
	this->items = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("assets/uiBacking.png");
	this->uiBackground = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
}

UIManager::~UIManager()
{
}

void UIManager::UpdateHealthBar(float _percentage)
{
	healthBar.w = maxBarLength * _percentage;
}

void UIManager::UpdateStaminaBar(float _percentage)
{
	staminaBar.w = maxBarLength * _percentage;
}


void UIManager::Draw()
{
	//Draw the backings
	SDL_RenderCopy(this->renderer, this->uiBackground, &backgroundSrc, &backgroundDest);
	SDL_RenderCopy(this->renderer, this->backing, &src, &healthBacking);
	SDL_RenderCopy(this->renderer, this->backing, &src, &staminaBacking);
	//Draw bars
	SDL_RenderCopy(this->renderer, this->health, &src, &healthBar);
	SDL_RenderCopy(this->renderer, this->stamina, &src, &staminaBar);

	//Draw the selected inventory
	if (drawInv) {
		itemSrc.x = 48;
		itemSrc.y = 48;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				itemDest.x = (j * itemSrc.w) + inventoryOffset.x;
				itemDest.y = (i * itemSrc.w) + inventoryOffset.y;
				SDL_RenderCopy(this->renderer, this->items, &itemSrc, &itemDest);
			}
		}
	}
}
