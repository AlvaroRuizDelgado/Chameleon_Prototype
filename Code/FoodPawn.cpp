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
	float x = Random::GetFloatRange(0.f, 1.f) * Resolution::Width();
	float y = Random::GetFloatRange(0.f, 0.6f) * Resolution::Height();
	m_bodyCircle->SetPosition(x, y);
	m_bodyCircle->SetSize(0.01f * Resolution::Width());
	m_bodyCircle->SetColor(0, 0, 0);
}


void FoodPawn::UpdateActor(float dtAsSeconds)
{
	Actor::UpdateActor(dtAsSeconds);


}

//void FoodPawn::Spawn()
//bool FoodPawn::CheckCollision(float x, float y)