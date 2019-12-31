#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Chameleon : public Actor, public sf::Drawable
{
private:
	static constexpr int NUM_LAYERS{ 3 };
	static constexpr float LAYER2_CHANGE_PER_SEC{ 1.6f };
	static constexpr float LAYER3_CHANGE_PER_SEC{ 0.8f };
	static constexpr float INITIAL_COLOR[3]{ 77.f / 255.f, 133.f / 255.f, 63.f / 255.f };

	sf::CircleShape m_spriteLayer [3];
	sf::Color m_color;

public:
	Chameleon(class Game* game);
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Getters / setters
	void SetColor(sf::Color);
	sf::Color GetColor() { return m_color; };
};
