#pragma once

#include "DrawComponent.h"
#include "Color.h"

class EyeComponent : public DrawComponent
{
public:
    EyeComponent(class Actor* owner, int drawPriority = 100);
    ~EyeComponent();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Getters / setter
    void SetSize(float R);
    void SetPosition(float X, float Y) { m_circle.setPosition(X, Y); };
    void SetOutlineThickness(float thickness) { m_circle.setOutlineThickness(thickness); };

private:
    sf::CircleShape m_circle;
};
