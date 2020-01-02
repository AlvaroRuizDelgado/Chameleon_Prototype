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

Color RectComponent::GetColor() const
{
    return Color(m_rectangle.getFillColor().r, m_rectangle.getFillColor().g, m_rectangle.getFillColor().b);
};

void RectComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_rectangle, states);
}
