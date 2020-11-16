#include "Gameloop.h"
#define FPSLOCK 60
#define FRAMETIME 1000/FPSLOCK
#undef main

Gameloop* gameloop;

unsigned int lastFrameTime, currentFrameTime = 0;

//Main method that gets called by the running of the program
int main(int argc, char* args[]) {
	
	gameloop = new Gameloop();
	if (!gameloop->Init()) {
		return 1;
	}
	
	//MAIN GAME LOOP
	while (gameloop->ProcessInput()) {
		//Update and draw the game
		gameloop->Update();
		gameloop->Draw();
		currentFrameTime = SDL_GetTicks();
		if (currentFrameTime - lastFrameTime < FRAMETIME) {
			SDL_Delay(FRAMETIME - (currentFrameTime - lastFrameTime));
			lastFrameTime = currentFrameTime;
		}
	}

	//Cleanup all of the game files
	gameloop->Clean();
	//Delete the gameloop instance
	delete gameloop;
	//Stop execution of program
	return 0;
}