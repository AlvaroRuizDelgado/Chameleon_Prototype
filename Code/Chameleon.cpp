#include "Chameleon.h"

#include <iostream>

#include "Game.h"
#include "RectComponent.h"
#include "Resolution.h"

Chameleon::Chameleon(Game* game, Color& color) :
    Actor(game)
    , m_color{ color }
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
    this->SetColor(Color(INITIAL_COLOR[0], INITIAL_COLOR[1], INITIAL_COLOR[2]));
    
    m_rectLayer[0]->SetPosition(0.35*Resolution::Width(), 0.2*Resolution::Height());
    m_rectLayer[0]->SetSize(0.3*Resolution::Width(), 0.25*Resolution::Height());
    
    m_rectLayer[1]->SetPosition(0.40*Resolution::Width(), 0.25*Resolution::Height());
    m_rectLayer[1]->SetSize(0.15*Resolution::Width(), 0.10*Resolution::Height());
    m_rectLayer[1]->SetColor(Color::RED);
    
    m_rectLayer[2]->SetPosition(0.43*Resolution::Width(), 0.28*Resolution::Height());
    m_rectLayer[2]->SetSize(0.06*Resolution::Width(), 0.04*Resolution::Height());
    m_rectLayer[2]->SetColor(Color::BLUE);
}

void Chameleon::SetColor(Color newColor)
{
    m_color.SetColor(newColor);
};

void Chameleon::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
    
    // Layer 0 changes color instantly for feedback, other layers morph by time
    m_rectLayer[0]->SetColor(m_color.GetRgb());
    float changeBudget = 0.f;
    for (int i = 1; i < NUM_LAYERS; ++i)
    {
        changeBudget = CHANGE_PER_SEC[i] * dtAsSeconds;
        Color morphedColor(m_rectLayer[i]->GetColor());
        morphedColor.MorphInto(m_color.GetRgb(), changeBudget);
        m_rectLayer[i]->SetColor(morphedColor);
    }
}
