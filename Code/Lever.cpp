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
        if (m_width > 3 * m_height)
        {
            m_percY = 0.5f;
            this->UpdateValue(static_cast<int>(m_percX * 255.f));
        }
        else if (m_height > 3 * m_width)
        {
            m_percX = 0.5f;
            this->UpdateValue(static_cast<int>(m_percY * 255.f));
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
    //m_value = newValue;
    //if (m_textEnabled)
    //{
    //    this->UpdateText();
    //}
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
    //m_beginC = beginning;
    //m_endC = end;
    sf::Color sfTopL(topL.R(), topL.G(), topL.B());
    sf::Color sfBotL(botL.R(), botL.G(), botL.B());
    sf::Color sfTopR(topR.R(), topR.G(), topR.B());
    sf::Color sfBotR(botR.R(), botR.G(), botR.B());
    m_box[0].color = sfTopL;     // Top-left
    m_box[1].color = sfBotL;     // Bottom-left
    m_box[2].color = sfTopR;     // Top-right
    m_box[3].color = sfBotR;     // Bottom-right
}

void Lever::SetHueGradient()
{
    // Make sure there are enough vertices
    if (m_box.size() != 14)
    {
        //this->InitBox(7);
        printf("Reducing vector of size %i\n", m_box.size());
        m_box.clear();
        printf("Now size %i\n", m_box.size());

        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height)));              // Bottom-left
        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height)));    // Bottom-right

        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height * 5 / 6)));
        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height * 5 / 6)));

        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height * 4 / 6)));
        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height * 4 / 6)));

        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height * 3 / 6)));
        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height * 3 / 6)));

        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height * 2 / 6)));
        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height * 2 / 6)));

        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height * 1 / 6)));
        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height * 1 / 6)));

        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY)));                         // Top-left
        m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY)));               // Top-right

        printf("Final size: %i\n", m_box.size());
    }

    int rgbMap[3][7] = { { 255, 255,   0,   0,   0, 255, 255 },
                         {   0, 255, 255, 255,   0,   0,   0 },
                         {   0,   0,   0, 255, 255, 255,   0 } };
    for (int i = 0; i < 7; ++i)
    {
        int R = rgbMap[0][i];
        int G = rgbMap[1][i];
        int B = rgbMap[2][i];
        printf("Color for %i: %i, %i ,%i\n", i, R, G, B);
        m_box[2*i].color = sf::Color(rgbMap[0][i], rgbMap[1][i], rgbMap[2][i]);
        m_box[2*i+1].color = sf::Color(rgbMap[0][i], rgbMap[1][i], rgbMap[2][i]);
    }
}

void Lever::InitBox(int numVertPairs)
{
    //printf("Clearing vector of size %i\n", m_box.size());
    //m_box.clear();
    //printf("Now size %i\n", m_box.size());

    //// Starting from the top, initialize vertices in the same height
    //for (int i = 0; i < numVertPairs; ++numVertPairs)
    //{
    //    m_box.push_back(sf::Vertex(sf::Vector2f(m_railX, m_railY + m_height * i / numVertPairs)));
    //    m_box.push_back(sf::Vertex(sf::Vector2f(m_railX + m_width, m_railY + m_height * i / numVertPairs)));
    //}
    //printf("Final size: %i\n", m_box.size());
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
    target.draw(m_lever, states);
    if (m_textEnabled)
    {
        target.draw(m_text, states);
    }
}
