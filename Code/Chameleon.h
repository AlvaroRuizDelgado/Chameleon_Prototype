#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "RectComponent.h"

class Chameleon : public Actor
{
private:
	static constexpr int NUM_LAYERS{ 3 };
	static constexpr float LAYER2_CHANGE_PER_SEC{ 1.6f };
	static constexpr float LAYER3_CHANGE_PER_SEC{ 0.8f };
	static constexpr float INITIAL_COLOR[3]{ 77.f / 255.f, 133.f / 255.f, 63.f / 255.f };

	sf::CircleShape m_spriteLayer [NUM_LAYERS];
	sf::Color m_color;
    
    RectComponent* m_rectLayer[NUM_LAYERS];

public:
	Chameleon(class Game* game);
    ~Chameleon();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

    // Getters / setters
	void SetColor(sf::Color);
	sf::Color GetColor() { return m_color; };
};
