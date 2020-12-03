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
<<<<<<< HEAD
=======

void Container::CheckForOpenCondition(Player* _player, bool _keysInp[])
{
	//Update the container with the player and key input
	if (unlocked && !open) {
		if (_keysInp[E]) {
			SDL_Rect nullRect;
			if (SDL_IntersectRect(this->GetEntityRect(), _player->GetEntityRect(), &nullRect)) {
				std::cout << "The container opens" << std::endl;
				this->OpenChest();
			}
		}
	}
}

void Container::CheckForCloseCondition(Player* _player)
{
	if (open) {
		SDL_Rect nullRect;
		if (!SDL_IntersectRect(this->GetEntityRect(), _player->GetEntityRect(), &nullRect)) {
			std::cout << "The container closes" << std::endl;
			CloseChest();
		}
	}
}
>>>>>>> parent of 0ffb9fb... Merge branch 'Developments'
