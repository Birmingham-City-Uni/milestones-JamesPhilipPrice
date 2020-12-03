#include "Container.h"

Container::Container(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health) : Entity(_startX, _startY, _textureLocation, _renderer, _movable, _damagable, _health)
{
	int x = 5;
	int y = 6;
	for (int i = 0; i < x; i++) {
		for (int o = 0; o < y; o++) {
			inventory[i][o] = static_cast<LootType>(rand() % ENUM_COUNT);
		}
	}
}

Container::~Container()
{
}

void Container::OpenChest()
{
	if (this->unlocked) {
		open = true;
	}
}

void Container::CloseChest()
{
	open = false;
}

void Container::UnlockChest()
{
	this->unlocked = true;
}

void Container::CheckForOpenCondition(Player* _player, bool _keysInp[])
{
	//Update the container with the player and key input
	if (unlocked && !open) {
		if (_keysInp[E]) {
			SDL_Rect nullRect;
			if (SDL_IntersectRect(this->GetEntityRect(), _player->GetEntityRect(), &nullRect)) {
				std::cout << "The container opens" << std::endl;
				std::cout << "Testing..." << std::endl;
				std::cout << "Container contents:" << std::endl;
				for (auto& i : inventory) {
					for (auto& o : i) {
						switch (o) {
						case Food:
							std::cout << "Food" << std::endl;
							break;
						case Water:
							std::cout << "Water" << std::endl;
							break;
						case Bolts:
							std::cout << "Bolts" << std::endl;
							break;
						case GunParts:
							std::cout << "Gun Parts" << std::endl;
							break;
						}
					}
				}
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
