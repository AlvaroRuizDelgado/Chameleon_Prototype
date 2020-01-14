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
    , m_percX{ 0.5f }
    , m_percY{ 0.5f }
    , m_beginC{ Color(0, 0, 0) }
    , m_endC{ Color(255, 255, 255) }
    , m_railX{ 0 }
    , m_railY{ 0 }
    , m_width{ 100 }
    , m_height{ 50 }
    , m_textEnabled{ false }
    , m_leverEnabled{ true }
    , m_textSpace{ 0.f }
    , m_orientation{ EOrientation::Vertical }
    , m_oneDimension{ false }
{
    m_owner->GetGame()->AddDrawable(this);
}

Lever::~Lever()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void Lever::Initialize()
{
    m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY)));                         // Top-left
    m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height)));              // Bottom-left
    m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY)));               // Top-right
    m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height)));    // Bottom-right
    this->SetE2EGradient(m_beginC, m_endC);
    
    // Selection pinpointer
    m_lever.setRadius(0.01f*Resolution::Height());
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
    if (x > m_railX
        && x < (m_railX + m_width)
        && y > m_railY
        && y < (m_railY + m_height))
    {
        // The distance will give me the value if inside the rail
        float distX = x - m_railX;
        float distY = y - m_railY;
        // Update the percentage values of the selector position
        m_percX = distX / m_width;
        m_percY = distY / m_height;

        // Balance the position of the selector if one dimensional
        if (m_oneDimension)
        {
            if (EOrientation::Horizontal == m_orientation)
            {
                m_percY = 0.5f;
                this->UpdateValue(static_cast<int>(m_percX * 255.f));
            }
            else if (EOrientation::Vertical == m_orientation)
            {
                m_percX = 0.5f;
                this->UpdateValue(static_cast<int>(m_percY * 255.f));
            }
        }
        this->UpdateLeverPosition();
        return true;
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

void Lever::UpdateValue(int newValue)
{
    m_value = newValue;
    if (m_textEnabled)
    {
        this->UpdateText();
    }
}

void Lever::SetValue(int newValue)
{
    // Balance the position of the selector if one dimensional
    if (m_width > 3 * m_height)
    {
        m_percY = 0.5f;
        m_percX = static_cast<float>(newValue)/255.f;
    }
    else if (m_height > 3 * m_width)
    {
        m_percX = 0.5f;
        m_percY = static_cast<float>(newValue) / 255.f;
    }
    this->UpdateLeverPosition();
    this->UpdateValue(newValue);
}

void Lever::SetPercentages(float percX, float percY)
{
    m_percX = percX;
    m_percY = percY;
    this->UpdateLeverPosition();
}

void Lever::UpdateLeverPosition()
{
    // The rail ranges [0, 255]
    float x =   m_railX                   // m_rail horizontal origin
                + m_percX * m_width       // value offset (0.5f for vertical levers)
                - m_lever.getRadius();    // radius offset

    // Radius may be > height of the rail, so it should overflow in each side.
    float y =   m_railY                 // m_rail vertical origin
                + m_percY * m_height    // value offset (0.5f for horizontal levers)
                - m_lever.getRadius();  // radius offset

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
    m_box[2].color = sfEnd;           // Top-right
    m_box[3].color = sfEnd;           // Bottom-right
}

void Lever::SetBoxGradient(Color topL, Color botL, Color topR, Color botR)
{
    sf::Color sfTopL(topL.R(), topL.G(), topL.B());
    sf::Color sfBotL(botL.R(), botL.G(), botL.B());
    sf::Color sfTopR(topR.R(), topR.G(), topR.B());
    sf::Color sfBotR(botR.R(), botR.G(), botR.B());
    m_box[0].color = sfTopL;     // Top-left
    m_box[1].color = sfBotL;     // Bottom-left
    m_box[2].color = sfTopR;     // Top-right
    m_box[3].color = sfBotR;     // Bottom-right
}

void Lever::SetHueGradient(float topSat, float botSat, float topBright, float botBright)
{
    // Make sure there are enough vertices
    if (m_box.size() != 14)
    {
        this->InitBox(7);
    }

    int rgbMap[3][7] = { { 255, 255,   0,   0,   0, 255, 255 },
                         {   0, 255, 255, 255,   0,   0,   0 },
                         {   0,   0,   0, 255, 255, 255,   0 } };
    //printf("Pre color size %i\n", m_box.size());
    for (int i = 0; i < 7; ++i)
    {
        //printf("Color for %i: %i, %i ,%i\n", i, rgbMap[0][i], rgbMap[1][i], rgbMap[2][i]);
        Color hueColor(rgbMap[0][i], rgbMap[1][i], rgbMap[2][i]);

        hueColor.SetSaturation(topSat);
        hueColor.SetBrightness(topBright);
        m_box[2*i].color = sf::Color(hueColor.R(), hueColor.G(), hueColor.B());

        hueColor.SetSaturation(botSat);
        hueColor.SetBrightness(botBright);
        m_box[2*i+1].color = sf::Color(hueColor.R(), hueColor.G(), hueColor.B());

        //m_box[2*i].color = sf::Color(rgbMap[0][i], rgbMap[1][i], rgbMap[2][i]);
        //m_box[2*i+1].color = sf::Color(rgbMap[0][i], rgbMap[1][i], rgbMap[2][i]);
    }
}

void Lever::InitBox(int numVertPairs)
{
    printf("Clearing vector of size %i\n", m_box.size());
    m_box.clear();
    //printf("Now size %i\n", m_box.size());

    // If vertical -> starting from the bottom, initialize vertices in the same height
    if (EOrientation::Vertical == m_orientation)
    {
        for (int i = numVertPairs - 1; i >= 0; --i)
        {
            float deltaY = m_height * static_cast<float>(i) / static_cast<float>(numVertPairs - 1);
            m_box.push_back(sf::Vertex(sf::Vector2f(m_railX,            m_railY + deltaY)));
            m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width,  m_railY + deltaY )));
        }
    }
    // If horizontal -> starting from the left, initialize vertices in the same X position
    else // if (EOrientation::Horizontal == m_orientation)
    {
        //for (int i = 0; i < numVertPairs; i)
        for (int i = 0; i < numVertPairs; ++i)
        //for (int i = numVertPairs - 1; i >= 0; --i)
        {
            float deltaX = m_width * static_cast<float>(i) / static_cast<float>(numVertPairs - 1);
            m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + deltaX, m_railY)));
            m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + deltaX, m_railY + m_height)));
        }
    }
    printf("Final size: %i\n", m_box.size());
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
    target.draw(&m_box[0], m_box.size(), sf::TriangleStrip);
    if (m_leverEnabled)
    {
        target.draw(m_lever, states);
    }
    if (m_textEnabled)
    {
        target.draw(m_text, states);
    }
}
