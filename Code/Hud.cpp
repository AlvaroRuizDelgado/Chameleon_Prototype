#include "Hud.h"

#include <iostream>
#include "Game.h"

Hud::Hud(Game* game) :
    Actor(game)
    , m_stamina{ 100.f }
{
}

void Hud::Initialize()
{
}

void Hud::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    //target.draw(m_targetColorDisplay, states);
}