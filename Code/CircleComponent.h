#pragma once

#include <SFML/Graphics.hpp>
#include "DrawComponent.h"

class CircleComponent : public DrawComponent
{
public:
    CircleComponent(class Actor* owner, int drawPriority = 100);
    ~CircleComponent();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    // Getters / setter
    void SetSize(float radius);
    void SetPosition(float newX, float newY);
    void SetColor(sf::Color newColor);
//    void SetColor(unsigned int newColor[]);
    sf::Color GetColor() const { return m_circle.getFillColor(); };
    void EnableOutline() { m_circle.setOutlineThickness(1.f); };
    void DisableOutline() { m_circle.setOutlineThickness(0.f); };
    
private:
    sf::CircleShape m_circle;
};
