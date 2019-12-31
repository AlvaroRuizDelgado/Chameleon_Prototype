#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "RectComponent.h"

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
    
    RectComponent* m_targetColorDisplay;
};
