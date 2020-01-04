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
    , m_percX{ 0.f }
    , m_percY{ 0.f }
    , m_beginC{ Color(0, 0, 0) }
    , m_endC{ Color(255, 255, 255) }
    , m_railX{ 0 }
    , m_railY{ 0 }
    , m_width{ 100 }
    , m_height{ 50 }
    , m_textEnabled{ false }
    , m_textSpace{ 0.f }
{
    m_owner->GetGame()->AddDrawable(this);
}

Lever::~Lever()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void Lever::Initialize()
{
    // Box, counter-clockwise from top-left
    m_box[0].position = sf::Vector2f(m_railX, m_railY);                         // Top-left
    m_box[1].position = sf::Vector2f(m_railX, m_railY + m_height);              // Bottom-left
    m_box[2].position = sf::Vector2f(m_railX + m_width, m_railY + m_height);    // Bottom-right
    m_box[3].position = sf::Vector2f(m_railX + m_width, m_railY);               // Top-right
    this->SetE2EGradient(m_beginC, m_endC);
    
    // Selection pinpointer
    m_lever.setRadius(0.01f*Resolution::Height());//1.5f*height/2);
    m_lever.setFillColor(sf::Color::Transparent);
    m_lever.setOutlineThickness(1.f);
    m_lever.setOutlineColor(sf::Color::Black);
    
    // Text
    if (m_textEnabled)
    {
        m_text.setFont(*(m_owner->GetGame()->GetFont()));
        m_text.setCharacterSize(Resolution::Height() / 60);
        m_text.setFillColor(sf::Color::Black);
        m_text.setOutlineColor(sf::Color::White);
        m_text.setOutlineThickness(1);
        m_text.setPosition(m_railX - m_textSpace, m_railY);
    }
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

void Lever::SetPosition(float x, float y)
{
    m_railX = x + m_textSpace;
    m_railY = y;
}

void Lever::SetSize(float width, float height)
{
    m_width = width - m_textSpace;    // Width considers both the text and the rail
    m_height = height;
}

void Lever::SetValue(int newValue)
{
    m_value = newValue;
    
    // Value 0 should lead to the center of the ball being on the rail origin.
    float x = m_railX                                       // m_rail origin
            - m_lever.getRadius()                           // radius offset
            + static_cast<float>(m_value)/255.f * m_width;  // value offset
    
    // Radius may be > height of the rail, so it should overflow in each side.
    float y = m_railY - (m_lever.getRadius() - m_height/2);
    
    m_lever.setPosition(x, y);
    if (m_textEnabled)
    {
        this->UpdateText();
    }
}

void Lever::SetPercentages(float percX, float percY)
{
    m_percX = percX;
    m_percY = percY;

    float x = m_railX + percX * m_width - m_lever.getRadius();
    float y = m_railY + percY * m_height - m_lever.getRadius();

    m_lever.setPosition(x, y);
}

void Lever::SetE2EGradient(Color beginning, Color end)
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

void Lever::SetBoxGradient(Color topL, Color botL, Color botR, Color topR)
{
    //m_beginC = beginning;
    //m_endC = end;
    sf::Color sfTopL(topL.R(), topL.G(), topL.B());
    sf::Color sfBotL(botL.R(), botL.G(), botL.B());
    sf::Color sfBotR(botR.R(), botR.G(), botR.B());
    sf::Color sfTopR(topR.R(), topR.G(), topR.B());
    m_box[0].color = sfTopL;     // Top-left
    m_box[1].color = sfBotL;     // Bottom-left
    m_box[2].color = sfBotR;     // Bottom-right
    m_box[3].color = sfTopR;     // Top-right
}

void Lever::SetHueGradient()
{

}

void Lever::EnableText()
{
    m_textEnabled = true;
    m_textSpace = Resolution::Width() * 0.06f;
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
    if (m_textEnabled)
    {
        target.draw(m_text, states);
    }
}
