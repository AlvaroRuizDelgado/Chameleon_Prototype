#include "Chameleon.h"
#include "Game.h"
#include <iostream>

Chameleon::Chameleon(Game* game) :
    Actor(game)
{
}

void Chameleon::Initialize()
{
    m_color = sf::Color::Green;
    for (int i = 0; i < NUM_LAYERS; ++i)
    {
        m_spriteLayer[i].setOutlineColor(sf::Color::White);
        m_spriteLayer[i].setOutlineThickness(1);

    }
    m_spriteLayer[0].setRadius(150.f);
    m_spriteLayer[0].setPosition(sf::Vector2f(100.f, 60.f));
    m_spriteLayer[0].setFillColor(m_color);

    m_spriteLayer[1].setRadius(50.f);
    m_spriteLayer[1].setPosition(sf::Vector2f(150.f, 100.f));
    m_spriteLayer[1].setFillColor(sf::Color::Red);

    m_spriteLayer[2].setRadius(20.f);
    m_spriteLayer[2].setPosition(sf::Vector2f(180.f, 130.f));
    m_spriteLayer[2].setFillColor(sf::Color::Blue);
}

void Chameleon::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}

void Chameleon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    for (int i = 0; i < NUM_LAYERS; ++i)
    {
        target.draw(m_spriteLayer[i], states);
    }
}