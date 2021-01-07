#pragma once
#include "Entity.h"
#include "UIManager.h"
#define WALKSPEED 0.1;
#define RUNSPEED 0.3;

class Player : public Entity {
public:
	Player(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health, LevelSystem* _level, UIManager* _ui);
	~Player();

	void ProcessInput(bool _keys[], float _mX, float _mY);
	void Draw();

	void DamagePlayer(float _damage);
	bool DepleteStamina();

	bool CheckIfExtracting();

	void CheckLifeState(int* _score);
	void ResetPlayer();

private:
	//Extract stuff
	SDL_Point extractPos = {64, 416};
	SDL_Rect extractSrc = {0, 0, 128, 128};
	SDL_Rect extractDest = {0, 0, 128, 128};
	SDL_Texture* extractTexture;
	int extractRadius = 64;
	int maxTimeToExtract = 1500;
	int timeLeftToExtract = maxTimeToExtract;
	float timeReductionAmount = 1;
	//Other stuff
	SDL_Rect src = { 0, 0, 256, 256 };
	SDL_Rect dest = { 0, 0, 256, 256 };
	SDL_Renderer* renderer;
	SDL_Texture* viewCone;
	bool canRun = true;
	int maxStamina = 100;
	float stamina = maxStamina;
	float staminaDepleteRate = 0.2;
	int mDeltaX, mDeltaY;
	UIManager* ui;
	const int ID = 69;
};
