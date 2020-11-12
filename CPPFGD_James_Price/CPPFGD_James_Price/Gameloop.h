#pragma once
#include <SDL.h>
#include "LevelSystem.h"

class Gameloop {
public:
	Gameloop();
	bool Init();
	bool ProcessInput();
	void Update();
	void Draw();
	void Clean();

	bool getKeyDown(int keyCode) {
		if (keyCode > 0 && keyCode < 512) {
			return this->keyDown[keyCode];
		}
		return false;
	}

private:
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	SDL_Window* window;
	SDL_Renderer* renderer;
	LevelSystem* level;
	bool keyDown[512];
};
