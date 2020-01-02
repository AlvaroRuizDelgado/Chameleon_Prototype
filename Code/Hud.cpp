#include "Hud.h"

#include <iostream>

#include "Game.h"
#include "RectComponent.h"
#include "Resolution.h"

Hud::Hud(Game* game) :
    Actor(game)
    , m_stamina{ 100.f }
{
    m_targetColorDisplay = new RectComponent(this, 100);
}

Hud::~Hud()
{
    delete m_targetColorDisplay;
}

void Hud::Initialize()
{
    // Display target color
    m_targetColorDisplay->SetPosition(0.05*Resolution::Width(), 0.03*Resolution::Height());
    m_targetColorDisplay->SetSize(0.1*Resolution::Width(), 0.05*Resolution::Height());
    m_targetColorDisplay->SetColor(GetGame()->GetTargetColor());
}

void Hud::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
    m_targetColorDisplay->SetColor(GetGame()->GetTargetColor());
}
