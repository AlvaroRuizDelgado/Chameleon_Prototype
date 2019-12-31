#include "Chameleon.h"
#include "Game.h"
#include <iostream>

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
    m_color = sf::Color::Green;
    
    m_rectLayer[0]->SetSize(200.f, 200.f);
    m_rectLayer[0]->SetPosition(150.f, 100.f);
    m_rectLayer[0]->SetColor(m_color);

    m_rectLayer[1]->SetSize(100.f, 100.f);
    m_rectLayer[1]->SetPosition(180.f, 130.f);
    m_rectLayer[1]->SetColor(sf::Color::Red);

    m_rectLayer[2]->SetSize(40.f, 40.f);
    m_rectLayer[2]->SetPosition(200.f, 150.f);
    m_rectLayer[2]->SetColor(sf::Color::Blue);
}

void Chameleon::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}
