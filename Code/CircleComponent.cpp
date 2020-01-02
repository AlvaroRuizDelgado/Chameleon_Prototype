#include "CircleComponent.h"
#include "Actor.h"
#include "Game.h"

CircleComponent::CircleComponent(Actor* owner, int drawPriority) :
    DrawComponent(owner, drawPriority)
{
    m_circle.setOutlineColor(sf::Color::White);
    this->SetOutlineThickness(1.f);
    
    m_owner->GetGame()->AddDrawable(this);
}

CircleComponent::~CircleComponent()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void CircleComponent::SetSize(float radius)
{
    m_circle.setRadius(radius);
}

void CircleComponent::SetPosition(float newX, float newY)
{
    m_circle.setPosition(newX, newY);
}

void CircleComponent::SetColor(sf::Color newColor)
{
//    sf::Color fillColor(newColor[0], newColor[1], newColor[2]);
    m_circle.setFillColor(newColor);
}

void CircleComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_circle, states);
}
