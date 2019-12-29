#include <iostream>

#include "Game.h"

int main(int argc, char const** argv)
{
	std::cout << "Chameleon greets you.\n\n";

	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();

	return EXIT_SUCCESS;
}