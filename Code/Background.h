#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Color.h"

class Background : public Actor
{
private:
	static constexpr float INITIAL_CHANGE_PER_SEC{ 0.4f };
	const float INITIAL_COLOR[3]{ 77.f / 255.f, 133.f / 255.f, 63.f / 255.f };

	float m_currentColor[3];
//	sf::Color m_rgbCurrentColor;
    sf::Color m_rgbCurrentColor;
	float m_targetColor[3];
	sf::Color m_rgbTargetColor;
	float m_changePerSec;

    class RectComponent* m_bgColor;

private:
	void NewTargetColor();
	sf::Color FloatToRgb(float color[]) const;

public:
	Background(class Game* game);
    ~Background();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;
    
    // Getters / setters
	sf::Color GetCurrentColor() const { return m_rgbCurrentColor; };
	sf::Color GetTargetColor() const { return m_rgbTargetColor; };
};
