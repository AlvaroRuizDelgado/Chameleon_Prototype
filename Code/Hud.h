#pragma once

#include <SFML/Graphics.hpp>

class Hud : public sf::Drawable
{
public:
	Hud();
	void initialize();
	void update(float dtAsSeconds);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape m_staminaBar;
	float m_stamina;

};