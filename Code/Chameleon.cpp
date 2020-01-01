#include "Chameleon.h"

#include <iostream>

#include "Game.h"
#include "RectComponent.h"
#include "Resolution.h"

Chameleon::Chameleon(Game* game) :
    Actor(game)
{
    for (int i = 0; i < NUM_LAYERS; ++i)
    {
        m_rectLayer[i] = new RectComponent(this, 20+10*i);
    }
}

Chameleon::~Chameleon()
{
    for (auto layer : m_rectLayer)
    {
        delete layer;
    }
}

void Chameleon::Initialize()
{
//    m_color = sf::Color::Green;
    this->SetColor(sf::Color::Green);
    
    m_rectLayer[0]->SetPosition(0.35*Resolution::Width(), 0.2*Resolution::Height());
    m_rectLayer[0]->SetSize(0.3*Resolution::Width(), 0.25*Resolution::Height());
    
    m_rectLayer[1]->SetPosition(0.40*Resolution::Width(), 0.25*Resolution::Height());
    m_rectLayer[1]->SetSize(0.15*Resolution::Width(), 0.10*Resolution::Height());
    m_rectLayer[1]->SetColor(sf::Color::Red);
    
    m_rectLayer[2]->SetPosition(0.43*Resolution::Width(), 0.28*Resolution::Height());
    m_rectLayer[2]->SetSize(0.06*Resolution::Width(), 0.04*Resolution::Height());
    m_rectLayer[2]->SetColor(sf::Color::Blue);
}

void Chameleon::SetColor(sf::Color newColor)
{
    m_color = newColor;
    m_rectLayer[0]->SetColor(m_color);
};

void Chameleon::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}
