#include "Container.h"

Container::Container(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health, LevelSystem* _level) : Entity(_startX, _startY, _textureLocation, _renderer, _movable, _damagable, _health, _level)
{
	this->renderer = _renderer;
	SDL_Surface* temp = IMG_Load("assets/Items.png");
	items = SDL_CreateTextureFromSurface(this->renderer, temp);
	SDL_FreeSurface(temp);
	int y = 5;
	int x = 6;
	for (int i = 0; i < y; i++) {
		for (int o = 0; o < x; o++) {
			inventory[i][o] = static_cast<LootType>(rand() % ENUM_C);
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

bool Container::CheckForOpenCondition(Player* _player, bool _keysInp[])
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
				return true;
			}
		}
	}
	return false;
}

bool Container::CheckForCloseCondition(Player* _player)
{
	if (open) {
		SDL_Rect nullRect;
		if (!SDL_IntersectRect(this->GetEntityRect(), _player->GetEntityRect(), &nullRect)) {
			std::cout << "The container closes" << std::endl;
			CloseChest();
			return true;
		}
	}
	return false;
}

bool Container::IsChestOpen()
{
	return open;
}

bool Container::TryTakeNextItem()
{
	if (SDL_GetTicks() - lastItemTake > itemTakeWaitTicks) {
		//remove the next item in the list
		bool removed = false;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				if (inventory[i][j] != Empty) {
					inventory[i][j] = Empty;
					removed = true;
					break;
				}
			}
			if (removed) {
				break;
			}
		}
		//Return
		lastItemTake = SDL_GetTicks();
		return removed;
	}
	return false;
}

int Container::GetInvetorySlotItem(int _x, int _y)
{
	return (int)inventory[_y][_x];
}

void Container::DrawInv()
{
	if (open) {
		//We need to get the item at the specific inventory slot
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				switch (inventory[i][j]) {
				case Empty:
					itemSrc.x = 48;
					itemSrc.y = 48;
					break;
				case Food:
					itemSrc.x = 0;
					itemSrc.y = 0;
					break;
				case Water:
					itemSrc.x = 16;
					itemSrc.y = 0;
					break;
				case Bolts:
					itemSrc.x = 32;
					itemSrc.y = 0;
					break;
				case GunParts:
					itemSrc.x = 48;
					itemSrc.y = 0;
					break;
				default:
					itemSrc.x = 48;
					itemSrc.y = 48;
					break;
				}
				itemDest.x = (j * itemSrc.w) + inventoryOffset.x;
				itemDest.y = (i * itemSrc.w) + inventoryOffset.y;
				itemDest.w = itemSrc.w;
				itemDest.h = itemSrc.h;
				SDL_RenderCopy(this->renderer, this->items, &itemSrc, &itemDest);
			}
		}
	}
}
