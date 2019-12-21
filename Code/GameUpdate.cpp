#include "Game.h"

void Game::update(float dtAsSeconds)
{
	if (State::PLAYING == m_state)
	{
		m_bgColor.r += 1;
		m_bgColor.g += 1;
		m_bgColor.b += 1;
		std::cout << "RGB: " 
			<< unsigned(m_bgColor.r) << " " 
			<< unsigned(m_bgColor.g) << " " 
			<< unsigned(m_bgColor.b) << std::endl;
	}
}