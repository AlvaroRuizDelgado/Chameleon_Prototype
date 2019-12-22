#include "Game.h"

void Game::update(float dtAsSeconds)
{
	if (State::PLAYING == m_state)
	{
		background.update(dtAsSeconds);
	}
}