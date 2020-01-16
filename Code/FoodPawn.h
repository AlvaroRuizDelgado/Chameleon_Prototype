#pragma once

#include "Actor.h"

class FoodPawn : public Actor
{
public:
	FoodPawn(class Game* game);
	~FoodPawn();

	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

	void Spawn();
	bool CheckCollision(float x, float y);

private:
	float m_velocity;
	class CircleComponent* m_bodyCircle;
};