#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Entity {
private:
	bool movable; //Whether the object is stationary
	bool damagable; //Use health or not
	float health;
	float x, y;
	float angle;
	SDL_Rect imageSrc;//Rect used for getting the src image
	SDL_Rect dimensions;//Position and size of entity
	SDL_Point center;//Center of the image used for rotation

	//Reference to the basics for drawing
	SDL_Renderer* renderer;
	SDL_Texture* texture;

public:
	Entity(int _startX, int _startY, const char* _textureLocation, SDL_Renderer* _renderer, bool _movable, bool _damagable, float _health);
	~Entity();

	bool InitializeBulletCollisions();

	void Move(float _movement[2]);
	void SetAngle(float _angle);
	float GetAngle();

	int GetOriginX();
	int GetOriginY();

	SDL_Rect* GetEntityRect();

	bool TakeDamage(float _damage) {
		//Damage object if possible, then return if the object is alive (or return true if damage doesn't apply)
		if (damagable) {
			std::cout << "Entity took damage" << std::endl;
			health -= _damage;
			return health > 0;
		}
		return true;
	}

	void Draw();
};