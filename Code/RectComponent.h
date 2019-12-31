#pragma once

#include <SFML/Graphics.hpp>
#include "DrawComponent.h"

class RectComponent : public DrawComponent
{
public:
    RectComponent(class Actor* owner, int drawPriority = 100);
    ~RectComponent();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    // Getters / setter
    void SetSize(float width, float height);
    void SetPosition(float newX, float newY);
    void SetColor(sf::Color newColor);
//    void SetColor(unsigned int newColor[]);
    sf::Color GetColor() const { return m_rectangle.getFillColor(); };
    
private:
    sf::RectangleShape m_rectangle;
//    float m_xPos;
//    float m_yPos;
//    float m_width;
//    float m_height;
};

