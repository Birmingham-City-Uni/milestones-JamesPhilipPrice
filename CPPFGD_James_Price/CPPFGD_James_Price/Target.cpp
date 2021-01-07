#include "Target.h"

Target::Target(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health, LevelSystem* _level) : Entity(_startX, _startY, _textureLocation, _renderer, _movable, _damagable, _health, _level)
{
	std::cout << "Creating a target!" << std::endl;
}

Target::~Target() {

}
