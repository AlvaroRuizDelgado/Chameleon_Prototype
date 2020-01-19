#include "Chameleon.h"

#include <iostream>

#include "EyeComponent.h"
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
        m_spriteLayer[i] = new SpriteComponent(this, 40 - 5*i);
    }
    m_spriteEyesWhite = new SpriteComponent(this, 15);
    for (int i = 0; i < NUM_EYES; ++i)
    {
        m_eyeComponent[i] = new EyeComponent(this, 100);
    }
}

Chameleon::~Chameleon()
{
    for (auto layer : m_spriteLayer)
    {
        delete layer;
    }
    for (auto eye : m_eyeComponent)
    {
        delete eye;
    }
    delete m_spriteEyesWhite;
}

void Chameleon::Initialize()
{
    this->SetColor(Color(INITIAL_COLOR[0], INITIAL_COLOR[1], INITIAL_COLOR[2]));
    
    float x = 0.53f * Resolution::Width();
    float y = 0.30f * Resolution::Height();
    float scale{ 0.35 };

    // White in the eyes
    m_spriteEyesWhite->SetTexture(TextureHolder::GetTexture("Resources/graphics/CammySpriteEyes.png"));
    m_spriteEyesWhite->SetPosition(x, y);
    m_spriteEyesWhite->SetScale(scale);

    // Black in the eyes
    m_eyeComponent[0]->SetSize(25.f *scale);
    m_eyeComponent[0]->SetPosition(x - 340 * scale, y - 187 * scale);

    m_eyeComponent[1]->SetSize(25.f * scale);
    m_eyeComponent[1]->SetPosition(x - 230 * scale, y - 183 * scale);

    // Could do a loop with sstream, but in this case I prefer to have flexibility
    m_spriteLayer[0]->SetTexture(TextureHolder::GetTexture("Resources/graphics/CammySprite0.png"));
    m_spriteLayer[0]->SetPosition(x, y);
    m_spriteLayer[0]->SetScale(scale);

    m_spriteLayer[1]->SetTexture(TextureHolder::GetTexture("Resources/graphics/CammySprite1.png"));
    m_spriteLayer[1]->SetPosition(x, y);
    m_spriteLayer[1]->SetScale(scale);

    m_spriteLayer[2]->SetTexture(TextureHolder::GetTexture("Resources/graphics/CammySprite2.png"));
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
