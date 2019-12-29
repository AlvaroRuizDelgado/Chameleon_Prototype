#pragma once

class Component
{
public:
	Component(class Actor* actor, int updateOrder = 100);
	virtual ~Component();

	void Update(float dtAsSeconds);

	int GetUpdateOrder() { return m_updateOrder; };

private:
	// Owning actor
	class Actor* m_owner;
	int m_updateOrder;
};