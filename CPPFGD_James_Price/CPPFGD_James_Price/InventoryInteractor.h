#pragma once
#include <SDL.h>

class InventoryInteractor {
public:
	InventoryInteractor();
	~InventoryInteractor();

private:
	SDL_Renderer* renderer;

	//Menu background
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundSrc;
	SDL_Rect backgroundDest;

	//The junk items
	SDL_Texture* junkItemsTexture;
	SDL_Rect junkSrc;
	SDL_Rect junkDest;
};