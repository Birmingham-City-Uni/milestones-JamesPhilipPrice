#pragma once
#include <SDL.h>
#include "LevelSystem.h"
#include "Player.h"
#include "Target.h"
#include "BulletManager.h"

class Gameloop {
public:
	Gameloop();
	bool Init();
	bool ProcessInput();
	void Update();
	void Draw();
	void Clean();


private:
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	int mouseX, mouseY;
	SDL_Window* window;
	SDL_Renderer* renderer;
	LevelSystem* level;
	Player* player;
	Target* target;
	BulletManager* bulletManager;
};
