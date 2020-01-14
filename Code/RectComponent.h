#pragma once

#include "DrawComponent.h"
#include "Color.h"

class RectComponent : public DrawComponent
{
public:
    RectComponent(class Actor* owner, int drawPriority = 100);
    ~RectComponent();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    bool CheckCollision(float x, float y);
    
    // Getters / setter
    void SetSize(float width, float height) { m_rectangle.setSize(sf::Vector2f(width, height)); };
    void SetPosition(float X, float Y) { m_rectangle.setPosition(X, Y); };
    void SetColor(Color c) { m_rectangle.setFillColor(sf::Color(c.R(), c.G(), c.B())); };
    void SetColor(int r, int g, int b) { m_rectangle.setFillColor(sf::Color(r, g, b)); };
    void SetColor(const int c[]) { m_rectangle.setFillColor(sf::Color(c[0], c[1], c[2])); };
    Color GetColor() const;
    void SetOutlineThickness(float thickness) { m_rectangle.setOutlineThickness(thickness); };
    float GetX() { return m_rectangle.getPosition().x; };
    float GetY() { return m_rectangle.getPosition().y; };
    float GetWidth() { return m_rectangle.getSize().x; };
    float GetHeight() { return m_rectangle.getSize().y; };
    
private:
    sf::RectangleShape m_rectangle;
};

