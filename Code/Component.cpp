#include "Component.h"
#include "Actor.h"

Component::Component(class Actor* owner, int updateOrder) :
	m_owner{ owner }
	, m_updateOrder{ updateOrder }
{
	// Add to actor's vector of components
	m_owner->AddComponent(this);
}

Component::~Component()
{
	m_owner->RemoveComponent(this);
}

void Component::Update(float dtAsSeconds)
{

}