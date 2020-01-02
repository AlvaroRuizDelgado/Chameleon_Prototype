#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Color.h"

class Background : public Actor
{
private:
	static constexpr float INITIAL_CHANGE_PER_SEC{ 0.4f };
	const float INITIAL_COLOR[3]{ 77.f / 255.f, 133.f / 255.f, 63.f / 255.f };

    Color m_bgColor;
    Color m_targetColor;
//	float m_targetColorF[3];
//	sf::Color m_targetColorInt;
	float m_changePerSec;

    class RectComponent* m_colorComp;

private:
	void NewTargetColor();
	sf::Color FloatToRgb(float color[]) const;

public:
	Background(class Game* game);
    ~Background();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;
    
    // Getters / setters
	sf::Color GetCurrentColor() const { return sf::Color(m_bgColor.R(), m_bgColor.G(), m_bgColor.B()); };
	sf::Color GetTargetColor() const { return sf::Color(m_targetColor.R(), m_targetColor.G(), m_targetColor.B()); };
};
