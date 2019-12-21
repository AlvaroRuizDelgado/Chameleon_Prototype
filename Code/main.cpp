#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	std::cout << "Hello chameleon";

	sf::RenderWindow window(sf::VideoMode(640, 480), "Chameleon");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		// update
		window.clear();

		// draw
		window.display();
	}

	return EXIT_SUCCESS;
}