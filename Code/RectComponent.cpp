#include "RectComponent.h"
#include "Actor.h"
#include "Game.h"

RectComponent::RectComponent(Actor* owner, int drawPriority) :
    DrawComponent(owner, drawPriority)
{
    m_rectangle.setOutlineColor(sf::Color::White);
    this->EnableOutline();
    
    m_owner->GetGame()->AddDrawable(this);
}

RectComponent::~RectComponent()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void RectComponent::SetSize(float width, float height)
{
    m_rectangle.setSize(sf::Vector2f(width, height));
}

void RectComponent::SetPosition(float newX, float newY)
{
    m_rectangle.setPosition(newX, newY);
}

void RectComponent::SetColor(sf::Color newColor)
{
//    sf::Color fillColor(newColor[0], newColor[1], newColor[2]);
    m_rectangle.setFillColor(newColor);
}

void RectComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_rectangle, states);
}
