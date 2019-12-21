#include "Game.h"

void Game::input()
{
	// Handle events by polling
	sf::Event event;
	float mouseX{ -1 };
	float mouseY{ -1 };

	while (m_window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//if (State::MAIN_MENU == m_state)
			//{
				m_window.close();
				return;
			//}
			//m_state = State::MAIN_MENU;
		}

		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		}
		if (State::PLAYING == m_state)
		{

		}
	}
}