#include "RgbLevers.h"

#include <iostream>
#include <sstream>

#include "Game.h"
#include "Lever.h"
#include "RectComponent.h"
#include "Resolution.h"
#include "TextComponent.h"

RgbLevers::RgbLevers(Game* game, Color& color) :
    Actor(game)
    , m_color{ color }
    , m_levers{ nullptr }
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
    // BACKGROUND
    m_background->SetPosition(0.05f*Resolution::Width(), 0.7f*Resolution::Height());
    m_background->SetSize(0.44f*Resolution::Width(), 0.17f*Resolution::Height());
    m_background->SetColor(170, 170, 190);
    
    // RGB LEVERS
    float yOffset = 0.04f;
    for (int i = 0; i < 3; ++i)
    {
        m_levers[i]->EnableText();
        m_levers[i]->SetPosition(0.06f * Resolution::Width(), (0.72f + i * yOffset) * Resolution::Height());
        m_levers[i]->SetSize(0.41f * Resolution::Width(), 0.02f * Resolution::Height());
        m_levers[i]->SetValue(0);
        m_levers[i]->SetOrientation(Lever::EOrientation::Horizontal);
        m_levers[i]->SetOneDimention();
        m_levers[i]->Initialize();

        // Set the initial gradients to show pure RGB
        int leverC[3]{ 0 };
        leverC[i] = 255;
        m_levers[i]->SetE2EGradient(Color(0,0,0), Color(leverC[0], leverC[1], leverC[2]));
    }
    
    // HEXADECIMAL TAG
    m_hexaTag->Initialize(0.06f*Resolution::Width(), (0.72f+3.f*yOffset)*Resolution::Height(),L"Testing");
}

bool RgbLevers::CheckCollision(float x, float y)
{
    if (m_background->CheckCollision(x, y))
    {
        for (int i = 0; i < 3; ++i)
        {
            if(m_levers[i]->CheckCollision(x, y))
            {
                printf("  - Collision with RGB lever %i\n", i);
                // Set Chameleon's new color
                m_color.SetRgb(m_levers[0]->GetValue(), m_levers[1]->GetValue(), m_levers[2]->GetValue());
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
    this->UpdateColor();
}

void RgbLevers::UpdateColor()
{
    const int* color = m_color.GetRgb();
    for (int i = 0; i < 3; ++i)
    {
        m_levers[i]->SetValue(color[i]);
        this->AdjustGradients(i);
    }
    this->SetHexaTag(m_color);
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
            m_levers[i]->SetE2EGradient(Color(beginC[0], beginC[1], beginC[2]),
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
