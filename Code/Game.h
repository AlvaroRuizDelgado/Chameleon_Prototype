#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Background.h"

class Game
{
private:
	static constexpr int FPS{ 60 };

	enum class State
	{
		MAIN_MENU, PLAYING, PAUSED, GAME_OVER
	};
	State m_state{ State::PLAYING };

	sf::RenderWindow m_window;
	//sf::Color m_bgColor{ sf::Color(77, 133, 63) };

	sf::Time m_gameTimeTotal{ sf::Time::Zero };

	int m_score{ 0 };

	Background background;

public:
	Game();
	void run();

private:
	void input();
	void update(float dtAsSeconds);
	void draw();

	void initializeGame();
};