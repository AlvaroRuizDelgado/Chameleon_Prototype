#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class Chameleon : public sf::Drawable
{
public:
	Chameleon();
	static constexpr int NUM_LAYERS{ 3 };

private:
	sf::CircleShape m_spriteLayer [3];

public:
	void initialize();
	void update(float dtAsSeconds);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};