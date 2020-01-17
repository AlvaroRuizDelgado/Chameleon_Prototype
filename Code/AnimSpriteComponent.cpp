#include "AnimSpriteComponent.h"

#include "Actor.h"
#include "Game.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawPriority) :
	SpriteComponent(owner, drawPriority)
	, m_animFps{ 0.2f }
	, m_currentFrame{ 0.f }
{
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::Update(float dtAsSeconds)
{
	SpriteComponent::Update(dtAsSeconds);

	//if (m_animTextures.size() > 0)
	if (m_animPositions.size() > 0)
	{
		m_currentFrame += m_animFps * dtAsSeconds;

		// Wrap current frame if needed
		while (m_currentFrame >= m_animPositions.size())
		{
			m_currentFrame -= m_animPositions.size();
		}

		//SetTexture(*m_animTextures[static_cast<int>(m_currentFrame)]);
		SpriteComponent::SetTextureRect(m_animPositions[static_cast<int>(m_currentFrame)]);
	}
}

void AnimSpriteComponent::SetAnimPositions(const std::vector<sf::IntRect>& animPositions)
{
	m_animPositions = animPositions;
	m_currentFrame = 0.f;
}