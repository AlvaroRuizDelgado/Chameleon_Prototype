#pragma once

#include "DrawComponent.h"
#include "Color.h"

class CircleComponent : public DrawComponent
{
public:
    CircleComponent(class Actor* owner, int drawPriority = 100);
    ~CircleComponent();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    bool CheckCollision(float x, float y);
    
    // Getters / setter
    void SetSize(float R) { m_circle.setRadius(R); };
    void SetPosition(float X, float Y) { m_circle.setPosition(X, Y); };
    void SetColor(Color c) { m_circle.setFillColor(sf::Color(c.R(), c.G(), c.B())); };
    void SetColor(int r, int g, int b) { m_circle.setFillColor(sf::Color(r, g, b)); };
    void SetColor(const int c[]) { m_circle.setFillColor(sf::Color(c[0], c[1], c[2])); };
    Color GetColor() const;
    void SetOutlineThickness(float thickness) { m_circle.setOutlineThickness(thickness); };
    
private:
    sf::CircleShape m_circle;
};
