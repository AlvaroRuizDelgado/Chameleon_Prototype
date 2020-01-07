#include "HsvLevers.h"

#include <iostream>

#include "Game.h"
#include "Lever.h"
#include "RectComponent.h"
#include "Resolution.h"

HsvLevers::HsvLevers(Game* game) :
    Actor(game)
    , m_hue{ 0.5f }
    , m_brightness{ 0.5f }
    , m_saturation{ 0.5f }
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
                                    Color(0, 0, 0),         // Bottom right
                                    Color(0, 0, 255));      // Top right
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
        if(m_brightSatBox->CheckCollision(x, y))
        {
            std::cout << "  - Collision with bright/sat box\n";
            m_saturation = m_brightSatBox->GetPercX();
            m_brightness = m_brightSatBox->GetPercX();
            this->GetGame()->SetChameleonColor(this->GetColor());
            return true;
        }
        if (m_hueLever->CheckCollision(x, y))
        {
            std::cout << "  - Collision with hue lever\n";
            m_hue = 1.f - m_hueLever->GetPercY();
            this->AdjustBrightSatBox();
            this->GetGame()->SetChameleonColor(this->GetColor());
            // Modify the background color of the brigthness / saturation box
            //this->AdjustGradients(i);
            return true;
        }
    }
    return false;
}

void HsvLevers::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}

Color HsvLevers::GetColor() const
{
    Color hsvColor(0, 0, 0);
    hsvColor.SetHue(m_hue);
    hsvColor.SetSaturation(m_saturation);
    hsvColor.SetBrightness(m_brightness);
    return hsvColor;
}

void HsvLevers::SetColor(Color newColor)
{
    int* color = newColor.GetRgb();
    //for (int i = 0; i < 3; ++i)
    //{
    //    m_levers[i]->SetValue(color[i]);
    //    this->AdjustGradients(i);
    //}
}

void HsvLevers::AdjustBrightSatBox()
{
    Color hueColor(0, 0, 0);
    hueColor.SetHue(m_hue);
    hueColor.SetSaturation(1.f);
    hueColor.SetBrightness(1.f);
    m_brightSatBox->SetBoxGradient( Color(255, 255, 255),   // Top left
                                    Color(0, 0, 0),         // Bottom left
                                    Color(0, 0, 0),         // Bottom right
                                    hueColor);      // Top right
}

//void HsvLevers::AdjustGradients(int changedLever)
//{
//    // Modify the gradient of the levers to show the options
//    for (int i = 0; i < 3; ++i)
//    {
//        if (changedLever != i)
//        {
//            int* endC = m_levers[i]->GetEndColor().GetRgb();
//            endC[changedLever] = m_levers[changedLever]->GetValue();
//            int* beginC = m_levers[i]->GetBeginColor().GetRgb();
//            beginC[changedLever] = m_levers[changedLever]->GetValue();
//            m_levers[i]->SetGradient(Color(beginC[0], beginC[1], beginC[2]),
//                                     Color(endC[0], endC[1], endC[2]));
//        }
//    }
//}

