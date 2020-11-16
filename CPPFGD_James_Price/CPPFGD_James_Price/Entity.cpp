#include "Entity.h"

Entity::Entity(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health) {
	std::cout << "Parent class constructor" << std::endl;
	//Set the basic attribute of the entity
	movable = _movable;
	damagable = _damagable;
	health = _health;
	dimensions.x = _startX;
	dimensions.y = _startY;
	imageSrc.x = imageSrc.y = 0;

	//Set the attributes relevant to the texture loading and rendering
	this->renderer = _renderer;
	SDL_Surface* tempSurface = IMG_Load(_textureLocation);
	imageSrc.w = dimensions.w = tempSurface->w;
	imageSrc.h = dimensions.h = tempSurface->h;
	texture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

Entity::~Entity() {
	std::cout << "Parent class deconstructor" << std::endl;
}

void Entity::Move(float _movement[2]) {
	x += _movement[0];
	y += _movement[1];
	dimensions.x = x;
	dimensions.y = y;
}

void Entity::Draw() {
	SDL_RenderCopy(this->renderer, this->texture, &imageSrc, &dimensions);
}

