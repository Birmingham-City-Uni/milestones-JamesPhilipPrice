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
}

UIManager::~UIManager()
{
}

void UIManager::Draw()
{
	//Draw the backings
	SDL_RenderCopy(this->renderer, this->backing, &src, &healthBacking);
	SDL_RenderCopy(this->renderer, this->backing, &src, &staminaBacking);

	SDL_RenderCopy(this->renderer, this->health, &src, &healthBar);
	SDL_RenderCopy(this->renderer, this->stamina, &src, &staminaBar);
}
