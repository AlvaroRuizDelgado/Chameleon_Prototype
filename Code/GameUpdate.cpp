#include "Game.h"

void Game::update(float dtAsSeconds)
{
	if (State::PLAYING == m_state)
	{
		m_background.update(dtAsSeconds);
		m_chameleon.update(dtAsSeconds);
		m_hud.update(dtAsSeconds);
	}
}