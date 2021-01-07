#include "Entity.h"
#include "RayCasting.h"

Entity::Entity(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health, LevelSystem* _level) {
	std::cout << "Parent class constructor" << std::endl;
	//Set the basic attribute of the entity
	movable = _movable;
	damagable = _damagable;
	startingHealth = _health;
	health = _health;
	dimensions.x = x = _startX;
	dimensions.y = y = _startY;
	imageSrc.x = imageSrc.y = 0;
	alive = true;

	//Collsion detection ray casting
	movementRay = new Ray;
	rayTools = new RayCastingTools();

	//Set the attributes relevant to the texture loading and rendering
	this->renderer = _renderer;
	SDL_Surface* tempSurface = IMG_Load(_textureLocation);
	imageSrc.w = dimensions.w = tempSurface->w;
	imageSrc.h = dimensions.h = tempSurface->h;
	center.x = dimensions.w / 2;
	center.y = dimensions.h / 2;
	texture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	this->level = _level;
}

Entity::~Entity() {
	std::cout << "Parent class deconstructor" << std::endl;
}

void Entity::Move(float _movement[2]) {
	movementRay->edge.start.x = GetOriginX();
	movementRay->edge.start.y = GetOriginY();
	movementRay->edge.end = movementRay->edge.start;
	movementRay->edge.end.x += _movement[0]*10;
	movementRay->edge.end.y += _movement[1]*10;
	movementRay->intersected = false;

	if (movementRay->edge.end.x >= 0 && movementRay->edge.end.x <= 1280 && movementRay->edge.end.y >= 0 && movementRay->edge.end.y <= 640) {
		for (auto& i : level->collsionEdgePool) {
			bool result = rayTools->CheckIntersection(&movementRay->edge, &i);
			if (result) {
				movementRay->intersected = true;
				break;
			}
		}
		if (!movementRay->intersected) {
			x += _movement[0];
			y += _movement[1];
		}
	}

	dimensions.x = x;
	dimensions.y = y;
}

SDL_Rect* Entity::GetEntityRect() {
	return &dimensions;
}

void Entity::SetAngle(float _angle) {
	angle = _angle;
}

float Entity::GetAngle() {
	return angle;
}

bool Entity::GetLifeState()
{
	return alive;
}

void Entity::SetLifeState(bool _state)
{
	alive = _state;
}

void Entity::ResetHealth()
{
	health = startingHealth;
	alive = true;
}

void Entity::ResetPosition()
{
	x = 0;
	y = 0;
	dimensions.x = x;
	dimensions.y = y;
}

float Entity::GetHealthPercentage()
{
	return health/startingHealth;
}

int Entity::GetOriginX() {
	return x + center.x;
}

int Entity::GetOriginY() {
	return y + center.y;
}

void Entity::Draw() {
	SDL_RenderCopyEx(this->renderer, this->texture, &imageSrc, &dimensions, angle, NULL, SDL_FLIP_NONE);
}

