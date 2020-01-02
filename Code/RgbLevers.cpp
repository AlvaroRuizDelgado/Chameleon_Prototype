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
    float redY = 0.72;
    for (int i = 0; i < 3; ++i)
    {
        // Initialize( Position  /  Size  /  Initial value of the lever
        m_levers[i]->Initialize(0.1*Resolution::Width(), (redY+i*0.04)*Resolution::Height(),
                                0.32*Resolution::Width(), 0.02*Resolution::Height(),
                                0);
    }
    this->SetColor(INITIAL_COLOR[0], INITIAL_COLOR[1], INITIAL_COLOR[2]);
    
//    // Text
//    for (int i = 0; i < 4; ++i)
//    {
//        m_colorsText[i].setFont(font);
//        m_colorsText[i].setCharacterSize(Resolution::Height()/100);
//        m_colorsText[i].setFillColor(sf::Color::White);
//        m_colorsText[i].setOutlineColor(sf::Color::Black);
//        m_colorsText[i].setOutlineThickness(1);
//        m_colorsText[i].setPosition(0.1*Resolution::Width(), (redY+i*0.04)*Resolution::Height());
//    }
//    m_colorsText[0].setString(L"R");
//    m_colorsText[1].setString(L"G");
//    m_colorsText[2].setString(L"B");
//    m_colorsText[3].setString(L"Hexadecimal: ");
    
}

//void FpsCounter::update(float dtAsSeconds)
//{
//    int fps = static_cast<int>(1/dtAsSeconds);
//    std::stringstream ss;
//    ss << "FPS = " << fps;
//    fpsText_.setString(ss.str());
//}


void RgbLevers::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
}

Color RgbLevers::GetColor()
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
