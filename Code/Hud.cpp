#include "Hud.h"

Hud::Hud()
{

}

void Hud::initialize()
{
    m_targetColorDisplay.setSize(sf::Vector2f(120.f, 50.f));
    m_targetColorDisplay.setOutlineColor(sf::Color::White);
    m_targetColorDisplay.setOutlineThickness(1);
    m_targetColorDisplay.setPosition(sf::Vector2f(10.f, 20.f));
    m_targetColorDisplay.setFillColor(sf::Color::Red);
}

void Hud::update(float dtAsSeconds)
{

}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    target.draw(m_targetColorDisplay, states);
}