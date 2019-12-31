#include "Hud.h"

#include <iostream>
#include "Game.h"

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
    m_targetColorDisplay->SetSize(120.f, 50.f);
    m_targetColorDisplay->SetPosition(10.f, 20.f);
    m_targetColorDisplay->SetColor(GetGame()->GetTargetColor());
}

void Hud::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
    m_targetColorDisplay->SetColor(GetGame()->GetTargetColor());
}
