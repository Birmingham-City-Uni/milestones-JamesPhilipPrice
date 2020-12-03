#include "Container.h"

Container::Container(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health) : Entity(_startX, _startY, _textureLocation, _renderer, _movable, _damagable, _health)
{
}

Container::~Container()
{
}

void Container::OpenChest()
{
	if (this->unlocked) {
		//Do shit
	}
}

void Container::UnlockChest()
{
	this->unlocked = true;
}
