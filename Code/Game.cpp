#include "Game.h"

#include <iostream>

Game::Game()
{
	m_window.create(sf::VideoMode(640, 480), "Chameleon");
	m_window.setFramerateLimit(FPS);
}

void Game::run()
{
	sf::Clock clock;

	// TEMPORARY
	initializeGame();

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();
		m_gameTimeTotal += dt;

		input();
		update(dt.asSeconds());
		draw();
	}
}

void Game::initializeGame()
{
	m_background.initialize();
	m_hud.initialize();
	m_chameleon.initialize();
}