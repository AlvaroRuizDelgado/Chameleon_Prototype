#include <iostream>

#include "Game.h"

int main(int, char const**)
{
	std::cout << "Chameleon greets you.\n\n";

	Game game;
	game.run();

	return EXIT_SUCCESS;
}