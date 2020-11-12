#include<iostream>
#include "Gameloop.h"

Gameloop::Gameloop() {
	//Pointers to the SDL window and renderer
	window = nullptr;
	renderer = nullptr;
	//Create the array for keypresses
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
}

bool Gameloop::Init() {
	//Initialise the SDL video and check for error (init will return a negative code if error occurs)
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Could not initialise the video: " << SDL_GetError();
		return false;
	}

	//Create the SDL window
	window = SDL_CreateWindow("Knockov",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	//Check if the window was created correctly and assigned
	if (window == nullptr) {
		std::cerr << "Could not create the SDL window: " << SDL_GetError();
		return false;
	}

	//Create the renderer
	renderer = SDL_CreateRenderer(window, - 1, SDL_RENDERER_ACCELERATED);

	level = new LevelSystem(renderer);

	//Check if the renderer was created properly
	if (renderer == nullptr) {
		std::cerr << "Could not create the renderer" << SDL_GetError();
		return false;
	}
	
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}

	return true;
}

bool Gameloop::ProcessInput() {
	SDL_Event e;

	//Get the input for the game
	while (SDL_PollEvent(&e)) {
		//In this program, the only event we're
		//worried about is when the user closes the window.
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = true;
			}
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = false;
			}
		}
		return true;
	}
	return true;
}

void Gameloop::Update() {

}

void Gameloop::Draw()
{
	//Clear the renderer
	SDL_RenderClear(renderer);
	//Render stuff
	level->DrawMap();

	//Push the frame to the window
	SDL_RenderPresent(renderer);
}

void Gameloop::Clean()
{
	//Clean the memory
}