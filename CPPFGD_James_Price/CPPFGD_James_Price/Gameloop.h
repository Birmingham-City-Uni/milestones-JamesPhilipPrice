#pragma once
#include <SDL.h>
#include "TextRenderer.h"
#include "LevelSystem.h"
#include "Player.h"
#include "Target.h"
#include "BulletManager.h"
#include "EnemyAIManager.h"
#include "UIManager.h"

class Gameloop {
public:
	Gameloop();
	bool Init();
	bool ProcessInput();
	void Update();
	void Draw();
	void Clean();
	int score = 0;

private:
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	int mouseX, mouseY;
	bool looting;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TextRenderer* textRenderer;
	UIManager* uiManager;
	LevelSystem* level;
	Player* player;
	Target* target;
	BulletManager* bulletManager;
	EnemyAIManager* enemyManager;
};
