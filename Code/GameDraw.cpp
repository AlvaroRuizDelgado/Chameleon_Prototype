#include "Game.h"

void Game::draw()
{
	if (State::PLAYING == m_state)
	{
		background.draw(m_window, sf::RenderStates::Default);
		m_window.clear(background.getCurrentColor());
	}

	m_window.display();
}