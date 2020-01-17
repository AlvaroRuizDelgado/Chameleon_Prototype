#pragma once

#include "Actor.h"

class FoodPawn : public Actor
{
public:
	FoodPawn(class Game* game);
	~FoodPawn();

	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

    // The actor can spawn in any edge over the color menus.
	void Spawn(float verticalLimit, float horizontalLimit = 1.f);
	bool CheckCollision(float x, float y);

private:
	float m_velocity;
    float m_verticalLimit;
    float m_horizontalLimit;
	class CircleComponent* m_bodyCircle;
	class AnimSpriteComponent* m_animSprite;
};
