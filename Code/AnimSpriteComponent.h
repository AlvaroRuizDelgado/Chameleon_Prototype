#pragma once

#include <SFML/Graphics.hpp>

#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawPriority = 100);
	~AnimSpriteComponent();

	void Update(float dtAsSeconds) override;
	bool CheckCollision(float x, float y) override;
		
	void SetAnimPositions(const std::vector<sf::IntRect>& animPositions);
	float GetAnimFps() const { return m_animFps; };
	void SetAnimFps(float fps) { m_animFps = fps; };

private:
	std::vector<sf::IntRect> m_animPositions;
	float m_currentFrame;
	float m_animFps;
};