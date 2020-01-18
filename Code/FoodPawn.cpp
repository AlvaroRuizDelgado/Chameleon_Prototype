#include <cmath>

#include "AnimSpriteComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Random.h"
#include "Resolution.h"

#include "FoodPawn.h"

FoodPawn::FoodPawn(Game* game) :
	Actor(game)
    , m_animSprite{ nullptr }
    , m_horizontalLimit{ 1.f }
    , m_verticalLimit{ 0.7f }
{
    m_animSprite = new AnimSpriteComponent(this, 90);
}

FoodPawn::~FoodPawn()
{
    delete m_animSprite;
}

void FoodPawn::Initialize()
{
    Actor::m_velocity = 10; 
    // Set the animation: texture sheet, coordinates and FPS
    m_animSprite->SetTexture(TextureHolder::GetTexture("Resources/graphics/Bee.png"));
    std::vector<sf::IntRect> animPositions;
    for (int i = 0; i < 4; ++i)
    {
        animPositions.push_back(sf::IntRect(128 * i, 0, 128, 128));
    }
    m_animSprite->SetAnimPositions(animPositions);
    m_animSprite->SetAnimFps(40.f);

    // Position and scale
    m_animSprite->SetPosition(m_position[0], m_position[1]);
    m_animSprite->SetScale(1.f);
}


void FoodPawn::UpdateActor(float dtAsSeconds)
{
	Actor::UpdateActor(dtAsSeconds);

    Actor::m_position[0] += Actor::m_velocity * std::cos(Actor::m_rotation);
    Actor::m_position[1] += Actor::m_velocity * std::sin(Actor::m_rotation);
    if (Actor::m_position[0] < 0.f
        || Actor::m_position[0] > m_horizontalLimit * Resolution::Width()
        || Actor::m_position[1] < 0.f
        || Actor::m_position[1] > m_verticalLimit * Resolution::Height())
    {
        this->Spawn(m_verticalLimit);
        printf("Out of boundaries at %f, %f\n", Actor::m_position[0], Actor::m_position[1]);
    }
    else
    {
        m_animSprite->SetPosition(Actor::m_position[0], Actor::m_position[1]);
    }
}

void FoodPawn::Spawn(float verticalLimit, float horizontalLimit)
{
    m_horizontalLimit = horizontalLimit;
    m_verticalLimit = verticalLimit;
    
    float midX = m_horizontalLimit/2.f;
    float midY = m_verticalLimit/2.f;
    
    float x = Random::GetFloatRange(0.f, 1.f) * Resolution::Width();
    float y = Random::GetFloatRange(0.f, 0.6f) * Resolution::Height();
    
    float distX = midX - x;
    float distY = midY - y;
    
    // Stick the spawn position to the nearest edge
    if (abs(distX) < abs(distY))
    {
        float signX = (distX > 0)? 1.f : -1.f;
        x = midX * (1.f - signX);
    }
    else
    {
        float signY = (distY > 0)? 1.f : -1.f;
        y = midY * (1.f - signY);
    }
    
    m_position[0] = x;
    m_position[1] = y;
    m_animSprite->SetPosition(m_position[0], m_position[1]);
    this->Initialize();
}

bool FoodPawn::CheckCollision(float x, float y)
{
    if (m_animSprite->CheckCollision(x, y))
    {
        this->Spawn(m_verticalLimit);
        return true;
    }
    return false;
}
