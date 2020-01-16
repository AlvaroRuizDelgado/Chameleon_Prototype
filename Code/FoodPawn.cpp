#include <cmath>

#include "Game.h"
#include "CircleComponent.h"
#include "Random.h"
#include "Resolution.h"

#include "FoodPawn.h"

FoodPawn::FoodPawn(Game* game) :
	Actor(game)
	, m_velocity{ 10.f }
	, m_bodyCircle{ nullptr }
{
	m_bodyCircle = new CircleComponent(this, 80);
}

FoodPawn::~FoodPawn()
{
	delete m_bodyCircle;
}

void FoodPawn::Initialize()
{
	m_bodyCircle->SetSize(0.01f * Resolution::Width());
	m_bodyCircle->SetColor(0, 0, 0);
    m_velocity = 10.f;
}


void FoodPawn::UpdateActor(float dtAsSeconds)
{
	Actor::UpdateActor(dtAsSeconds);

    m_position[0] += m_velocity * std::cos(m_rotation);
    m_position[1] += m_velocity * std::sin(m_rotation);
    if (m_position[0] < 0.f
        || m_position[0] > m_horizontalLimit * Resolution::Width()
        || m_position[1] < 0.f
        || m_position[1] > m_verticalLimit * Resolution::Height())
    {
        this->Spawn(m_verticalLimit);
        printf("Out of boundaries at %f, %f\n", m_position[0], m_position[1]);
    }
    else
    {
        m_bodyCircle->SetPosition(m_position[0], m_position[1]);
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
    m_bodyCircle->SetPosition(m_position[0], m_position[1]);
    this->Initialize();
}

bool FoodPawn::CheckCollision(float x, float y)
{
    if (m_bodyCircle->CheckCollision(x, y))
    {
        this->Spawn(m_verticalLimit);
        return true;
    }
    return false;
}
