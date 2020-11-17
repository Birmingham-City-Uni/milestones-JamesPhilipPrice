#include<iostream>
#include "Gameloop.h"


enum KeyStates {
	W = 0,
	A,
	S,
	D,
	ENUM_COUNT
};

bool keys[KeyStates::ENUM_COUNT];

Gameloop::Gameloop() {
	//Pointers to the SDL window and renderer
	window = nullptr;
	renderer = nullptr;
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

	//Check if the renderer was created properly
	if (renderer == nullptr) {
		std::cerr << "Could not create the renderer" << SDL_GetError();
		return false;
	}
	
	//CREATE THE MAIN GAME ELEMENTS
	level = new LevelSystem(renderer);

	player = new Player(0, 0, "assets/player.png", renderer, true, true, 100);

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
			//SORT OUT INPUT HERE!!!
			switch (e.key.keysym.sym) {
			case SDLK_w:
				keys[W] = true;
				break;
			case SDLK_a:
				keys[A] = true;
				break;
			case SDLK_s:
				keys[S] = true;
				break;
			case SDLK_d:
				keys[D] = true;
				break;
			default:
				break;
			}
		}
		else if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
			case SDLK_w:
				keys[W] = false;
				break;
			case SDLK_a:
				keys[A] = false;
				break;
			case SDLK_s:
				keys[S] = false;
				break;
			case SDLK_d:
				keys[D] = false;
				break;
			default:
				break;
			}
		}
		SDL_GetMouseState(&mouseX, &mouseY);

		return true;
	}
	return true;
}

void Gameloop::Update() {
	player->ProcessInput(keys, mouseX, mouseY);
}

void Gameloop::Draw()
{
	//Clear the renderer
	SDL_RenderClear(renderer);
	//Render stuff
	level->DrawMap();
	player->Draw();

	//Push the frame to the window
	SDL_RenderPresent(renderer);
}

void Gameloop::Clean()
{
	//Clean the memory
}