#include "Game.h"
#include "InitializationException.h"

#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

int main() {
	Game* game;

	try {
		game = new Game("C:/Den/Programming/TestProjects/PathGame/PathGameDemo/PathGame/info.xml");
	}
	catch (InitializationException) {
		return 1;
	}
	
	while (game->update());

	delete game;

	return 0;
}