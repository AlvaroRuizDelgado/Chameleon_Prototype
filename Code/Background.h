#pragma once

#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
private:
	static constexpr float INITIAL_CHANGE_PER_SEC{ 0.4f };
	static constexpr float INITIAL_COLOR[3]{ 77.f / 255.f, 133.f / 255.f, 63.f / 255.f };

	float m_currentColor[3];
	sf::Color m_rgbCurrentColor;
	float m_targetColor[3];
	sf::Color m_rgbTargetColor;
	float m_changePerSec;

	sf::RectangleShape m_targetColorDisplay;

private:
	void newTargetColor();
	sf::Color floatToRgb(float color[]) const;

public:
	Background();
	void initialize();
	void update(float dtAsSeconds);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Color getCurrentColor() { return m_rgbCurrentColor; };
	sf::Color getTargetColor() { return m_rgbTargetColor; };
};