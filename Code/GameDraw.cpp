#include "Game.h"

void Game::draw()
{
	if (State::PLAYING == m_state)
	{
		m_window.clear(m_bgColor);
	}

	m_window.display();
}