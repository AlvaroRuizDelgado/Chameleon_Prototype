#pragma once

#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
private:
	static constexpr float INITIAL_CHANGE_PER_SEC{ 0.005f };
	//static constexpr sf::Color INITIAL_COLOR = sf::Color(77, 133, 63);

	sf::Color m_currentColor; // { sf::Color(77, 133, 63) };
	float m_fineColor[3];
	//sf::Color m_targetColor{ sf::Color(77, 133, 63) };
	float m_targetColor[3];
	float m_changePerSec;

private:
	void setTargetColor();

public:
	Background();
	void initialize();
	void update(float dtAsSeconds);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Color getCurrentColor();
};