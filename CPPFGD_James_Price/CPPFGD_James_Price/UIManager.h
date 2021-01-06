#pragma once
#include<SDL.h>
#include<SDL_image.h>
class UIManager {
public:
	UIManager(SDL_Renderer* _renderer);
	~UIManager();

	void Draw();

private:
	SDL_Renderer* renderer;

	SDL_Texture* backing;
	SDL_Texture* health;
	SDL_Texture* stamina;

	SDL_Rect src = {0, 0, 32, 32};

	SDL_Rect healthBacking = {0, 700, 128, 8};
	SDL_Rect healthBar = { 0, 700, 128, 8 };
	SDL_Rect staminaBacking = { 0, 710, 128, 8 };
	SDL_Rect staminaBar = { 0, 710, 128, 8 };
};