#pragma once

class Component
{
public:
	Component(class Actor* actor, int updateOrder = 100);
	virtual ~Component();

	void Update(float dtAsSeconds);

    // Getters / setters
	int GetUpdateOrder() const { return m_updateOrder; };

protected:
	// Owning actor
	class Actor* m_owner;
	int m_updateOrder;
};
