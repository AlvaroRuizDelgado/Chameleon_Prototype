#include "Chameleon.h"

#include <iostream>

#include "Game.h"
#include "RectComponent.h"
#include "Resolution.h"
#include "SpriteComponent.h"
#include "TextureHolder.h"

Chameleon::Chameleon(Game* game, Color& color) :
    Actor(game)
    , m_color{ color }
{
    for (int i = 0; i < NUM_LAYERS; ++i)
    {
        m_spriteLayer[i] = new SpriteComponent(this, 40 - 10*i);
    }
    m_spriteEyes = new SpriteComponent(this, 15);
}

Chameleon::~Chameleon()
{
    for (auto layer : m_spriteLayer)
    {
        delete layer;
    }
    delete m_spriteEyes;
}

void Chameleon::Initialize()
{
    this->SetColor(Color(INITIAL_COLOR[0], INITIAL_COLOR[1], INITIAL_COLOR[2]));
    
    float x = 0.53f * Resolution::Width();
    float y = 0.30f * Resolution::Height();
    float scale{ 0.45 };

    m_spriteEyes->SetTexture("Resources/graphics/CammySpriteEyes.png");
    m_spriteEyes->SetPosition(x, y);
    m_spriteEyes->SetScale(scale);

    m_spriteLayer[0]->SetTexture("Resources/graphics/CammySprite0.png");
    m_spriteLayer[0]->SetPosition(x, y);
    m_spriteLayer[0]->SetScale(scale);

    m_spriteLayer[1]->SetTexture("Resources/graphics/CammySprite1.png");
    m_spriteLayer[1]->SetPosition(x, y);
    m_spriteLayer[1]->SetScale(scale);

    m_spriteLayer[2]->SetTexture("Resources/graphics/CammySprite2.png");
    m_spriteLayer[2]->SetPosition(x, y);
    m_spriteLayer[2]->SetScale(scale);
}

void Chameleon::SetColor(Color newColor)
{
    m_color.SetColor(newColor);
};

void Chameleon::UpdateActor(float dtAsSeconds)
{
    Actor::UpdateActor(dtAsSeconds);
    
    // Layer 0 changes color instantly for feedback, other layers morph by time
    m_spriteLayer[0]->SetColor(m_color);
    float changeBudget = 0.f;
    for (int i = 1; i < NUM_LAYERS; ++i)
    {
        changeBudget = CHANGE_PER_SEC[i] * dtAsSeconds;
        Color morphedColor(m_spriteLayer[i]->GetColor());
        morphedColor.MorphInto(m_color.GetRgb(), changeBudget);
        m_spriteLayer[i]->SetColor(morphedColor);
    }
}
