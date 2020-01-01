#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Chameleon : public Actor
{
public:
	Chameleon(class Game* game);
    ~Chameleon();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

    // Getters / setters
	void SetColor(sf::Color);
	sf::Color GetColor() { return m_color; };
    
private:
    static constexpr int NUM_LAYERS{ 3 };
    static constexpr float LAYER2_CHANGE_PER_SEC{ 1.6f };
    static constexpr float LAYER3_CHANGE_PER_SEC{ 0.8f };
    static constexpr float INITIAL_COLOR[3]{ 77.f / 255.f, 133.f / 255.f, 63.f / 255.f };

    sf::Color m_color;
    
    class RectComponent* m_rectLayer[NUM_LAYERS];
};
