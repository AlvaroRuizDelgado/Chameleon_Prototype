#include "Game.h"

void Game::draw()
{
	if (State::PLAYING == m_state)
	{
		m_window.clear(m_background.getCurrentColor());
		m_background.draw(m_window, sf::RenderStates::Default);
		m_chameleon.draw(m_window, sf::RenderStates::Default);
		m_hud.draw(m_window, sf::RenderStates::Default);
	}

	m_window.display();
}