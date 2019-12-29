#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Hud : public Actor, public sf::Drawable
{
public:
	Hud(class Game* game);
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape m_staminaBar;
	float m_stamina;
};