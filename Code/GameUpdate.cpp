#include "Game.h"

#include <iostream>

void Game::update(float dtAsSeconds)
{
	if (State::PLAYING == m_state)
	{
		m_background.update(dtAsSeconds);
		m_chameleon.update(dtAsSeconds);
		m_hud.update(dtAsSeconds);
	}
	sf::Color colorDiff = m_background.getCurrentColor() - m_chameleon.getColor();
	int totalColorDiff = abs(colorDiff.r) + abs(colorDiff.g) + abs(colorDiff.b);
	if (totalColorDiff > 100)
	{
		std::cout << "Very very different!!\n";
	}
}