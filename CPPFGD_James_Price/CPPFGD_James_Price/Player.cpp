#include<iostream>
#include "Player.h"
#include "Keys.h"

#define PI 3.14159265

Player::Player(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health, LevelSystem* _level, UIManager* _ui) : Entity(_startX, _startY, _textureLocation, _renderer, _movable, _damagable, _health, _level)
{
	std::cout << "Initialising player. Be on the lookout for the base class above! ^^^" << std::endl;
	renderer = _renderer;
	SDL_Surface* temp = IMG_Load("assets/visionCone.png");
	viewCone = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("assets/extractGlow.png");
	extractTexture = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
	extractDest.x = extractPos.x;
	extractDest.y = extractPos.y;
	ui = _ui;
}

Player::~Player() {

}

void Player::ProcessInput(bool _keys[], float _mX, float _mY)
{
	//Process Movement
	float direction[2] = { 0, 0 };
	if (_keys[W]) {
		direction[1] -= 1;
	}
	if (_keys[S]) {
		direction[1] += 1;
	}
	if (_keys[A]) {
		direction[0] -= 1;
	}
	if (_keys[D]) {
		direction[0] += 1;
	}

	if (_keys[SHIFT] && DepleteStamina() && canRun) {
		direction[0] *= RUNSPEED;
		direction[1] *= RUNSPEED;
	}
	else {
		if (stamina < maxStamina) {
			stamina += staminaDepleteRate;
			ui->UpdateStaminaBar(stamina / maxStamina);
		}
		else {
			canRun = true;
		}
		direction[0] *= WALKSPEED;
		direction[1] *= WALKSPEED;
	}
	

	Move(direction);

	//Process direction the player must face
	mDeltaX = GetOriginX() - _mX;
	mDeltaY = GetOriginY() - _mY;
	SetAngle((atan2(mDeltaY, mDeltaX) * (180/PI))-90);

}

void Player::Draw()
{
	//Draw vision cone
	dest.x = GetOriginX() - src.w / 2;
	dest.y = GetOriginY() - src.h / 2;
	SDL_RenderCopyEx(this->renderer, this->viewCone, &src, &dest, GetAngle(), NULL, SDL_FLIP_NONE);

	//Draw extraction
	SDL_RenderCopy(this->renderer, this->extractTexture, &extractSrc, &extractDest);
	Entity::Draw();
}

void Player::DamagePlayer(float _damage)
{
	std::cout << "Damaging player" << std::endl;
	TakeDamage(_damage);
	ui->UpdateHealthBar(GetHealthPercentage());
}

bool Player::DepleteStamina()
{
	if (stamina - staminaDepleteRate > 0) {
		stamina -= staminaDepleteRate;
		ui->UpdateStaminaBar(stamina / maxStamina);
		return true;
	}
	else {
		canRun = false;
		return false;
	}
}

bool Player::CheckIfExtracting()
{
	int disX = GetOriginX() - (extractPos.x + extractDest.w / 2);
	int disY = GetOriginY() - (extractPos.y + extractDest.h / 2);
	int disMag = (disX * disX) + (disY * disY);
	if (disMag < extractRadius) {
		timeLeftToExtract -= timeReductionAmount;
		if (timeLeftToExtract <= 0) {
			//Reset player but save score
			ResetPlayer();
		}
		return true;
	}
	else {
		timeLeftToExtract = maxTimeToExtract;
		return false;
	}

}

void Player::CheckLifeState(int* _score)
{
	if (!GetLifeState()) {
		*_score = 0;
		ResetPlayer();
	}
}

void Player::ResetPlayer()
{
	ResetHealth();
	ResetPosition();
}

