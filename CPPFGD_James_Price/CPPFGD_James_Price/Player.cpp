#include<iostream>
#include "Player.h"

enum KeyStates {
	W = 0,
	A,
	S,
	D,
	ENUM_COUNT
};

Player::Player(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health) : Entity(_startX, _startY, _textureLocation, _renderer, _movable, _damagable, _health)
{
	std::cout << "Initialising player. Be on the lookout for the base class above! ^^^" << std::endl;
}

Player::~Player() {

}

void Player::ProcessInput(bool _keys[])
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

	direction[0] *= WALKSPEED;
	direction[1] *= WALKSPEED;

	Move(direction);
}
