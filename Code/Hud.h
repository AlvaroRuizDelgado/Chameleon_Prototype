#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Hud : public Actor
{
public:
	Hud(class Game* game);
    ~Hud();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

private:
	sf::RectangleShape m_staminaBar;
	float m_stamina;
    
    class RectComponent* m_targetColorDisplay;
};
