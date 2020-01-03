#include "Lever.h"

#include <iostream>
#include <sstream>

#include "Actor.h"
#include "CircleComponent.h"
#include "Game.h"
#include "RectComponent.h"
#include "Resolution.h"

Lever::Lever(Actor* owner, int drawPriority) :
    DrawComponent(owner, drawPriority)
    , m_value{ 0 }
    , m_beginC{ Color(0, 0, 0) }
    , m_endC{ Color(255, 255, 255) }
{
    m_owner->GetGame()->AddDrawable(this);
}

Lever::~Lever()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void Lever::Initialize(float x, float y, float width, float height, int initValue)
{
    // Rail needs to leave space for the text box in the left side
    float textSpace = Resolution::Width() * 0.06f;
    
    m_railX = x + textSpace;
    m_railY = y;
    m_width = width - textSpace;    // Width considers both the text and the rail
    m_height = height;

    // Box, counter-clockwise from top-left
    m_box[0].position = sf::Vector2f(m_railX, m_railY);                      // Bottom-left
    m_box[1].position = sf::Vector2f(m_railX, m_railY + m_height);           // Bottom-right
    m_box[2].position = sf::Vector2f(m_railX + m_width, m_railY + m_height); // Top-right
    m_box[3].position = sf::Vector2f(m_railX + m_width, m_railY);            // Top-left
    this->SetGradient(m_beginC, m_endC);
    
    // Selection pinpointer
    m_lever.setRadius(1.5*height/2);
    m_lever.setFillColor(sf::Color::Black);
    m_lever.setOutlineThickness(1.f);
    
    // Text
    m_text.setFont(*(m_owner->GetGame()->GetFont()));
    m_text.setCharacterSize(Resolution::Height()/60);
    m_text.setFillColor(sf::Color::Black);
    m_text.setOutlineColor(sf::Color::White);
    m_text.setOutlineThickness(1);
    m_text.setPosition(x, y);
    
    this->SetValue(initValue);
}

bool Lever::CheckCollision(float x, float y)
{
    if (y > m_railY
        && y < (m_railY + m_height))
    {
        // The distance will give me the value if inside the rail
        float distance = x - m_railX;
        float width = m_width;
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
    float x = m_railX                                       // m_rail origin
            - m_lever.getRadius()                           // radius offset
            + static_cast<float>(m_value)/255.f * m_width;  // value offset
    
    // Radius is 1.5 the height of the rail, so it overflows 0.25 in each side.
    float y = m_railY - 0.25 * m_height;
    
    m_lever.setPosition(x, y);
    this->UpdateText();
}

void Lever::SetGradient(Color beginning, Color end)
{
    m_beginC = beginning;
    m_endC = end;
    sf::Color sfBeginning(m_beginC.R(), m_beginC.G(), m_beginC.B());
    sf::Color sfEnd(m_endC.R(), m_endC.G(), m_endC.B());
    m_box[0].color = sfBeginning;     // Top-left
    m_box[1].color = sfBeginning;     // Bottom-left
    m_box[2].color = sfEnd;           // Bottom-right
    m_box[3].color = sfEnd;           // Top-right
}

void Lever::UpdateText()
{
    std::stringstream ss;
    if (m_value > 99)
    {
        ss << "";
    }
    else
        if (m_value > 9)
    {
        ss << " ";
    }
    else
    {
        ss << "  ";
    }
    ss << m_value;
    m_text.setString(ss.str());
}

void Lever::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
//    states.transform *= getTransform();
    target.draw(m_box, 4, sf::Quads);
    target.draw(m_lever, states);
    target.draw(m_text, states);
}
