#pragma once

#include <SFML/Graphics.hpp>

#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawPriority = 100);
	~AnimSpriteComponent();

	void Update(float dtAsSeconds) override;

	void SetAnimTextures(const std::vector<sf::Texture*>& textures);
	float GetAnimFps() const { return m_animFps; };
	void SetAnimFps(float fps) { m_animFps = fps; };

private:
	std::vector<sf::Texture*> m_animTextures;
	float m_currentFrame;
	float m_animFps;
};