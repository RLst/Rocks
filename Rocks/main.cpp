#include "Game.h"
#include "GameDefines.h"

int main() {
	
	// allocation
	auto app = new Game();

	// initialise and loop
	app->run("Rocks v1.1", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	// deallocation
	delete app;

	return 0;
}