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

Color CircleComponent::GetColor() const
{
    return Color(m_circle.getFillColor().r, m_circle.getFillColor().g, m_circle.getFillColor().b);
};


void CircleComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_circle, states);
}
