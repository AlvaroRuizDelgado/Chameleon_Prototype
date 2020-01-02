#include "Lever.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Actor.h"
#include "CircleComponent.h"
#include "Game.h"
#include "RectComponent.h"
#include "Resolution.h"

Lever::Lever(Actor* owner, int drawPriority) :
    DrawComponent(owner, drawPriority)
    , m_value{ 0 }
{
    m_owner->GetGame()->AddDrawable(this);
}

Lever::~Lever()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void Lever::Initialize(float x, float y, float width, float height, int initValue)
{
    m_rail.setPosition(x, y);
    m_rail.setSize(sf::Vector2f(width, height));
    m_rail.setFillColor(sf::Color(200,200,200));   // Gray
    m_rail.setOutlineThickness(1.f);

    m_lever.setRadius(1.5*height/2);
    m_lever.setFillColor(sf::Color::Black);
    m_lever.setOutlineThickness(1.f);
    
    this->SetValue(initValue);
}

bool Lever::CheckCollision(float x, float y)
{
    if (y > m_rail.getPosition().y
        && y < (m_rail.getPosition().y + m_rail.getSize().y))
    {
        // The distance will give me the value if inside the rail
        float distance = x - m_rail.getPosition().x;
        float width = m_rail.getSize().x;
        if (distance >= 0
            && distance <= width)
        {
            this->SetValue(static_cast<int>(distance/width*255.f));
            return true;
        }
    }
    return false;
}

void Lever::SetValue(int newValue)
{
    m_value = newValue;
    
    // Value 0 should lead to the center of the ball being on the rail origin.
    float x = m_rail.getPosition().x                                    // m_rail origin
            - m_lever.getRadius()                                       // radius offset
            + static_cast<float>(m_value)/255.f * m_rail.getSize().x;   // value offset
    
    // Radius is 1.5 the height of the rail, so it overflows 0.25 in each side.
    float y = m_rail.getPosition().y - 0.25 * m_rail.getSize().y;
    
    m_lever.setPosition(x, y);
};

void Lever::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_rail, states);
    target.draw(m_lever, states);
}
