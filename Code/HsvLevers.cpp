#include "HsvLevers.h"

#include <iostream>

#include "Game.h"
#include "Lever.h"
#include "RectComponent.h"
#include "Resolution.h"

HsvLevers::HsvLevers(Game* game, Color& color) :
    Actor(game)
    , m_color{ color }
{
    m_background = new RectComponent(this, 20);
    m_hueLever = new Lever(this, 100);
    m_brightSatBox = new Lever(this, 100);
}

HsvLevers::~HsvLevers()
{
    delete m_hueLever;
    delete m_brightSatBox;
    delete m_background;
}

void HsvLevers::Initialize()
{
    // BACKGROUND
    m_background->SetPosition(0.51f*Resolution::Width(), 0.7f*Resolution::Height());
    m_background->SetSize(0.44f*Resolution::Width(), 0.17f*Resolution::Height());
    m_background->SetColor(170, 170, 190);
    
    // BRIGHTNESS / SATURATION BOX
    m_brightSatBox->SetPosition(0.53f * Resolution::Width(), 0.71f * Resolution::Height());
    m_brightSatBox->SetSize(0.34f * Resolution::Width(), 0.15f * Resolution::Height());
    m_brightSatBox->Initialize();
    m_brightSatBox->SetBoxGradient( Color(255, 255, 255),   // Top left
                                    Color(0, 0, 0),         // Bottom left
                                    Color(0, 0, 255),       // Top right
                                    Color(0, 0, 0));        // Bottom right
    m_brightSatBox->SetPercentages(0.5f, 0.5f);

    // HUE LEVER
    m_hueLever->SetPosition(0.88f * Resolution::Width(), 0.71f * Resolution::Height());
    m_hueLever->SetSize(0.05f * Resolution::Width(), 0.15f * Resolution::Height());
    m_hueLever->Initialize();
    m_hueLever->SetHueGradient();
    m_hueLever->SetPercY(0.5f);
}

bool HsvLevers::CheckCollision(float x, float y)
{
    if (m_background->CheckCollision(x, y))
    {
        if (m_hueLever->CheckCollision(x, y))
        {
            std::cout << "  - Collision with hue lever\n";
            //m_hue = 1.f - m_hueLever->GetPercY();
            m_color.SetHue(1.f - m_hueLever->GetPercY());
            this->AdjustBrightSatBox();
            return true;
        }
        if(m_brightSatBox->CheckCollision(x, y))
        {
            std::cout << "  - Collision with bright/sat box\n";
            m_color.SetSaturation(m_brightSatBox->GetPercX());
            m_color.SetBrightness(1.f - m_brightSatBox->GetPercY());
            printf("SV=(%.2f,%.2f)\n", m_color.GetSaturation(), m_color.GetBrightness());
            return true;
        }
    }
    return false;
}

void HsvLevers::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
    this->SetColor(m_color);
}

void HsvLevers::SetColor(Color newColor)
{
    m_color.SetHue(newColor.GetHue());
    m_hueLever->SetPercY(1.f - m_color.GetHue());
    this->AdjustBrightSatBox();

    m_color.SetSaturation(newColor.GetSaturation());
    m_color.SetBrightness(newColor.GetBrightness());
    m_brightSatBox->SetPercentages(m_color.GetSaturation(), 1.f - m_color.GetBrightness());
}

void HsvLevers::AdjustBrightSatBox()
{
    Color hueColor(0, 0, 0);
    hueColor.SetHue(m_color.GetHue());
    hueColor.SetSaturation(1.f);
    hueColor.SetBrightness(1.f);
    m_brightSatBox->SetBoxGradient( Color(255, 255, 255),   // Top left
                                    Color(0, 0, 0),         // Bottom left
                                    hueColor,               // Top right
                                    Color(0, 0, 0));        // Bottom right
}
