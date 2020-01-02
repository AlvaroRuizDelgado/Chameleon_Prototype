#include "RectComponent.h"

#include "Actor.h"
#include "Game.h"

RectComponent::RectComponent(Actor* owner, int drawPriority) :
    DrawComponent(owner, drawPriority)
{
    m_rectangle.setOutlineColor(sf::Color::White);
    this->SetOutlineThickness(1.f);
    
    m_owner->GetGame()->AddDrawable(this);
}

RectComponent::~RectComponent()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

bool RectComponent::CheckCollision(float x, float y)
{
    // I don't consider the case of negative width or height
    if (x > m_rectangle.getPosition().x
        && x < (m_rectangle.getPosition().x + m_rectangle.getSize().x)
        && y > m_rectangle.getPosition().y
        && y < (m_rectangle.getPosition().y + m_rectangle.getSize().y))
    {
        return true;
    }
    return false;
}

Color RectComponent::GetColor() const
{
    return Color(m_rectangle.getFillColor().r, m_rectangle.getFillColor().g, m_rectangle.getFillColor().b);
};

void RectComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_rectangle, states);
}
