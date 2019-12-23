#pragma once

#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
private:
	static constexpr float INITIAL_CHANGE_PER_SEC{ 0.4f };
	static constexpr float INITIAL_COLOR[3]{ 77.f / 255.f, 133.f / 255.f, 63.f / 255.f };

	sf::Color m_rgbColor;
	float m_currentColor[3];
	float m_targetColor[3];
	float m_changePerSec;

private:
	void newTargetColor();

public:
	Background();
	void initialize();
	void update(float dtAsSeconds);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Color getCurrentColor();
};