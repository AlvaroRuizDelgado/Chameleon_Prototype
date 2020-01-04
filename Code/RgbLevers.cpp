#include "RgbLevers.h"

#include <iostream>
#include <sstream>

#include "Game.h"
#include "Lever.h"
#include "RectComponent.h"
#include "Resolution.h"
#include "TextComponent.h"

RgbLevers::RgbLevers(Game* game) :
    Actor(game)
{
    m_background = new RectComponent(this, 20);
    for (int i = 0; i < 3; ++i)
    {
        m_levers[i] = new Lever(this, 100);
    }
    m_hexaTag = new TextComponent(this, 100);
}

RgbLevers::~RgbLevers()
{
    delete m_hexaTag;
    for (int i = 0; i < 3; ++i)
    {
        delete m_levers[i];
    }
    delete m_background;
}

void RgbLevers::Initialize()
{
    // Initialize levers background
    m_background->SetPosition(0.05*Resolution::Width(), 0.7*Resolution::Height());
    m_background->SetSize(0.44*Resolution::Width(), 0.17*Resolution::Height());
    m_background->SetColor(170, 170, 190);
    
    // Initialize levers
    float yOffset = 0.04;
    for (int i = 0; i < 3; ++i)
    {
        // Initialize( Position  /  Size  /  Initial value of the lever )
        m_levers[i]->Initialize(0.06*Resolution::Width(), (0.72+i*yOffset)*Resolution::Height(),
                                0.41*Resolution::Width(), 0.02*Resolution::Height(),
                                0);
        int leverC[3]{ 0 };
        leverC[i] = 255;
        m_levers[i]->SetGradient(Color(0,0,0), Color(leverC[0], leverC[1], leverC[2]));
    }
    
    // Initialize hexadecimal tag
    m_hexaTag->Initialize(0.06*Resolution::Width(), (0.72+3*yOffset)*Resolution::Height(),L"Testing");
    
    // Set the initial color value in all components
    this->SetColor(INITIAL_COLOR[0], INITIAL_COLOR[1], INITIAL_COLOR[2]);
}

bool RgbLevers::CheckCollision(float x, float y)
{
    if (m_background->CheckCollision(x, y))
    {
        std::cout << "  - Collision with RGB levers bg\n";
        for (int i = 0; i < 3; ++i)
        {
            if(m_levers[i]->CheckCollision(x, y))
            {
                // Set hexadecimal tag to new color
                this->SetHexaTag(this->GetColor());
                // Modify the gradient of the levers to show the options
                this->AdjustGradients(i);
                return true;
            }
        }
    }
    return false;
}

void RgbLevers::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}

Color RgbLevers::GetColor() const
{
    return Color(m_levers[0]->GetValue(), m_levers[1]->GetValue(), m_levers[2]->GetValue());
}

void RgbLevers::SetColor(Color newColor)
{
    int* color = newColor.GetRgb();
    for (int i = 0; i < 3; ++i)
    {
        m_levers[i]->SetValue(color[i]);
        this->AdjustGradients(i);
    }
    this->SetHexaTag(newColor);
}

void RgbLevers::SetColor(int r, int g, int b)
{
    this->SetColor(Color(r, g, b));
}

void RgbLevers::AdjustGradients(int changedLever)
{
    // Modify the gradient of the levers to show the options
    for (int i = 0; i < 3; ++i)
    {
        if (changedLever != i)
        {
            int* endC = m_levers[i]->GetEndColor().GetRgb();
            endC[changedLever] = m_levers[changedLever]->GetValue();
            int* beginC = m_levers[i]->GetBeginColor().GetRgb();
            beginC[changedLever] = m_levers[changedLever]->GetValue();
            m_levers[i]->SetGradient(Color(beginC[0], beginC[1], beginC[2]),
                                     Color(endC[0], endC[1], endC[2]));
        }
    }
}

void RgbLevers::SetHexaTag(Color color)
{
    std::wstringstream wstream;
    wstream << "    Color code: #" << color.GetHexa();
    m_hexaTag->SetText(wstream.str());
}
