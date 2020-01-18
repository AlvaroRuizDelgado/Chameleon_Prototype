#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <iostream>


Actor::Actor(class Game* game) :
	m_state{ State::Active }
	, m_position{ 0.f, 0.f }
	, m_scale{ 1.f }
	, m_rotation{ 0.f }
	, m_velocity{ 0.f }
	, m_game{ game }
{
	m_game->AddActor(this);
}

Actor::~Actor()
{
	m_game->RemoveActor(this);
	while (!m_components.empty())
	{
		delete m_components.back();
	}
}

void Actor::Update(float dtAsSeconds)
{
	if (State::Active == m_state)
	{
		UpdateComponents(dtAsSeconds);
		UpdateActor(dtAsSeconds);
	}
}

void Actor::UpdateActor(float dtAsSeconds)
{
}


void Actor::UpdateComponents(float dtAsSeconds)
{
	for (auto component : m_components)
	{
		component->Update(dtAsSeconds);
	}
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (the first element with order higher than this)
	int myOrder = component->GetUpdateOrder();
	auto iter = m_components.begin();
	for (; iter != m_components.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	m_components.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	if (m_components.end() != iter)
	{
		m_components.erase(iter);
	}
}
