#include "RgbLevers.h"

#include <iostream>

#include "Game.h"
#include "Lever.h"
#include "RectComponent.h"
#include "Resolution.h"

RgbLevers::RgbLevers(Game* game) :
    Actor(game)
{
    for (int i = 0; i < 3; ++i)
    {
        m_levers[i] = new Lever(this, 100);
    }
    m_background = new RectComponent(this, 20);
}

RgbLevers::~RgbLevers()
{
    delete m_background;
    for (int i = 0; i < 3; ++i)
    {
        delete m_levers[i];
    }
}

void RgbLevers::Initialize()
{
    // Levers background
    m_background->SetPosition(0.05*Resolution::Width(), 0.7*Resolution::Height());
    m_background->SetSize(0.4*Resolution::Width(), 0.2*Resolution::Height());
    m_background->SetColor(Color::RED);
    
    // Levers
    float yOffset = 0.04;
    for (int i = 0; i < 3; ++i)
    {
        // Initialize( Position  /  Size  /  Initial value of the lever
        m_levers[i]->Initialize(0.06*Resolution::Width(), (0.72+i*yOffset)*Resolution::Height(),
                                0.38*Resolution::Width(), 0.02*Resolution::Height(),
                                0);
    }
    this->SetColor(INITIAL_COLOR[0], INITIAL_COLOR[1], INITIAL_COLOR[2]);
}

bool RgbLevers::CheckCollision(float x, float y)
{
    if (m_background->CheckCollision(x, y))
    {
        std::cout << "  - Collision with RGB levers bg\n";
        for (auto lever : m_levers)
        {
            if(lever->CheckCollision(x, y))
            {
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
    m_levers[0]->SetValue(newColor.R());
    m_levers[1]->SetValue(newColor.G());
    m_levers[2]->SetValue(newColor.B());
}

void RgbLevers::SetColor(int r, int g, int b)
{
    m_levers[0]->SetValue(r);
    m_levers[1]->SetValue(g);
    m_levers[2]->SetValue(b);
}
