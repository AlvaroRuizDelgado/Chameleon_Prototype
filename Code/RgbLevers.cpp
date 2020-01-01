#include "RgbLevers.h"

#include <iostream>
#include <SFML/Graphics.hpp>

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
    m_background->SetPosition(0.05*Resolution::Width(), 0.7*Resolution::Height());
    m_background->SetSize(0.4*Resolution::Width(), 0.2*Resolution::Height());
    m_background->SetColor(sf::Color::Red);
    
    float redY = 0.72;
    for (int i = 0; i < 3; ++i)
    {
        // Initialize( Position  /  Size  /  Initial value of the lever
        m_levers[i]->Initialize(0.1*Resolution::Width(), (redY+i*0.04)*Resolution::Height(),
                                0.32*Resolution::Width(), 0.02*Resolution::Height(),
                                0);
    }
}

void RgbLevers::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}
