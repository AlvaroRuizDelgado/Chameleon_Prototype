#include "SpectrumLevers.h"

#include <iostream>

#include "Actor.h"
#include "Game.h"
#include "Lever.h"
#include "RectComponent.h"

SpectrumLevers::SpectrumLevers(Game* game, Color& color) :
    Actor(game)
    , m_color{ color }
{
    m_background = new RectComponent(this, 20);
    m_topBox = new Lever(this, 100);
    m_bottomBox = new Lever(this, 100);
}

SpectrumLevers::~SpectrumLevers()
{
    delete m_bottomBox;
    delete m_topBox;
    delete m_background;
}

void SpectrumLevers::Initialize()
{
    // BACKGROUND
    m_background->SetPosition(0.05f * Resolution::Width(), 0.88f * Resolution::Height());
    m_background->SetSize(0.9f * Resolution::Width(), 0.11f * Resolution::Height());
    m_background->SetColor(170, 170, 190);

    // TOP BOX LEVER
    m_topBox->SetPosition(0.06f * Resolution::Width(), 0.885f * Resolution::Height());
    m_topBox->SetSize(0.88f * Resolution::Width(), 0.05f * Resolution::Height());
    m_topBox->Initialize();
    // Saturation = [0, 1] / Brightness = 1
    m_topBox->SetOrientation(Lever::EOrientation::Horizontal);
    m_topBox->SetHueGradient(0.f, 1.f, 1.f, 1.f);

    // BOTTOM BOX LEVER
    m_bottomBox->SetPosition(0.06f * Resolution::Width(), 0.935f * Resolution::Height());
    m_bottomBox->SetSize(0.88f * Resolution::Width(), 0.05f * Resolution::Height());
    m_bottomBox->Initialize();
    // Saturation = 1 / Brightness = [1, 0]
    m_bottomBox->SetOrientation(Lever::EOrientation::Horizontal);
    m_bottomBox->SetHueGradient(1.f, 1.f, 1.f, 0.f);

    //this->UpdateColor();
}

bool SpectrumLevers::CheckCollision(float x, float y)
{
    if (m_background->CheckCollision(x, y))
    {
        if (m_topBox->CheckCollision(x, y))
        {
            std::cout << "  - Collision with top box\n";
            m_color.SetHue(m_topBox->GetPercX());
            m_color.SetSaturation(m_topBox->GetPercY());
            m_color.SetBrightness(1.f);
            m_topBox->EnableLever();
            m_bottomBox->DisableLever();
            return true;
        }
        if (m_bottomBox->CheckCollision(x, y))
        {
            std::cout << "  - Collision with bottom box\n";
            m_color.SetHue(m_bottomBox->GetPercX());
            m_color.SetSaturation(1.f);
            m_color.SetBrightness(1.f - m_bottomBox->GetPercY());
            m_topBox->DisableLever();
            m_bottomBox->EnableLever();
            return true;
        }
    }
    return false;
}

void SpectrumLevers::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
    this->UpdateColor();
}

void SpectrumLevers::UpdateColor()
{
    // Top box
    if (m_color.GetSaturation() < m_color.GetBrightness())
    {
        m_topBox->EnableLever();
        m_bottomBox->DisableLever();
        m_topBox->SetPercentages(m_color.GetHue(), m_color.GetSaturation());
    }
    // Bottom box
    else
    {
        m_topBox->DisableLever();
        m_bottomBox->EnableLever();
        m_bottomBox->SetPercentages(m_color.GetHue(), 1.f - m_color.GetBrightness());
    }
}