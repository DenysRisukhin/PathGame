#include "Game.h"
#include "InitException.h"

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

// GitHub
int main() {
	
	Game* game;

	try {
		game = new Game("C:/Den/Programming/GitHub/PathGame/info.xml");
	}
	catch (InitException) {
		return 1;
	}


	while (game->update());

	delete game;

	return 0;
}