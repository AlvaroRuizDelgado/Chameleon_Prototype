#include <iostream>

#include "Game.h"

int main(int, char const**)
{
	std::cout << "Hello chameleon\n\n";

	Game game;
	game.run();

	return EXIT_SUCCESS;
}