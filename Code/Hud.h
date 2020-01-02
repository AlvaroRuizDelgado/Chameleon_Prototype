#pragma once

#include "Actor.h"

class Hud : public Actor
{
public:
	Hud(class Game* game);
    ~Hud();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

private:
    // Stamina bar should be a drawable component
//	sf::RectangleShape m_staminaBar;
	float m_stamina;
    
    class RectComponent* m_targetColorDisplay;
};
