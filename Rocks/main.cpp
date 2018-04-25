#include "RocksApp.h"
#include "GameDefines.h"

int main() {
	
	// allocation
	auto app = new Game();

	// initialise and loop
	app->run("AIE", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	// deallocation
	delete app;

	return 0;
}