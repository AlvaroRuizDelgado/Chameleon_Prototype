#include "EyeComponent.h"

#include "Actor.h"
#include "Game.h"

EyeComponent::EyeComponent(Actor* owner, int drawPriority) :
    DrawComponent(owner, drawPriority)
{
    m_circle.setFillColor(sf::Color::Black);
    m_owner->GetGame()->AddDrawable(this);
}

EyeComponent::~EyeComponent()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void EyeComponent::SetSize(float R)
{
    m_circle.setRadius(R);
    m_circle.setOrigin(R, R);
    m_circle.setScale(1.f, 1.5f);
}

void EyeComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_circle, states);
}
