#include<iostream>
#include "Gameloop.h"
#include "Keys.h"

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
	textRenderer = new TextRenderer(renderer, "assets/fonts/Russian.ttf", 40);

	level = new LevelSystem(renderer);

	uiManager = new UIManager(renderer);

	player = new Player(0, 0, "assets/player.png", renderer, true, true, 100, level, uiManager);

	enemyManager = new EnemyAIManager(2, renderer, player, level, uiManager);

	bulletManager = new BulletManager(renderer, player, enemyManager, level);
	bulletManager->Init();

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
			case SDLK_e:
				keys[E] = true;
				break;
			case SDLK_LSHIFT:
				keys[SHIFT] = true;
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
			case SDLK_e:
				keys[E] = false;
				break;
			case SDLK_LSHIFT:
				keys[SHIFT] = false;
			default:
				break;
			}
		}
		//Mouse input
		SDL_GetMouseState(&mouseX, &mouseY);
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				keys[MOUSELEFT] = true;
				break;
			case SDL_BUTTON_RIGHT:
				keys[MOUSERIGHT] = true;
				break;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				keys[MOUSELEFT] = false;
				break;
			case SDL_BUTTON_RIGHT:
				keys[MOUSERIGHT] = false;
				break;
			}
		}

		return true;
	}
	return true;
}

void Gameloop::Update() {
	player->ProcessInput(keys, mouseX, mouseY);
	enemyManager->Update(keys);
	bulletManager->ProcessInput(keys);
	score += bulletManager->Update();
	player->CheckLifeState(&score);
}

void Gameloop::Draw()
{
	//Clear the renderer
	SDL_RenderClear(renderer);
	//Render stuff
	level->DrawMap();
	player->Draw();
	enemyManager->Draw();
	bulletManager->Draw();
	uiManager->Draw();
	enemyManager->DrawInvs();
	std::string scoreString = "Score: " + std::to_string(score);
	textRenderer->RenderString(scoreString, 1100, 640);

	//Push the frame to the window
	SDL_RenderPresent(renderer);
}

void Gameloop::Clean()
{
	//Clean the memory
	bulletManager->Clean();
}