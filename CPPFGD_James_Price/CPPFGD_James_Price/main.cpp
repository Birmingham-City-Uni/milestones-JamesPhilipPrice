#include "Gameloop.h"

#undef main

Gameloop* gameloop;

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
	}

	//Cleanup all of the game files
	gameloop->Clean();
	//Delete the gameloop instance
	delete gameloop;
	//Stop execution of program
	return 0;
}