#include "AnimSpriteComponent.h"

#include "Actor.h"
#include "Game.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawPriority) :
	SpriteComponent(owner, drawPriority)
	, m_animFps{ 0.f }
	, m_currentFrame{ 0.f }
{
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::Update(float dtAsSeconds)
{
	SpriteComponent::Update(dtAsSeconds);

	if (m_animTextures.size() > 0)
	{
		m_currentFrame += m_animFps * dtAsSeconds;

		// Wrap current frame if needed
		while (m_currentFrame >= m_animTextures.size())
		{
			m_currentFrame -= m_animTextures.size();
		}

		SetTexture(*m_animTextures[static_cast<int>(m_currentFrame)]);
	}
}


void AnimSpriteComponent::SetAnimTextures(const std::vector<sf::Texture*>& textures)
{
	m_animTextures = textures;
	m_currentFrame = 0.f;
}