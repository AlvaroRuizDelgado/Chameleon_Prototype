#pragma once

#include <vector>

class Actor
{
public:
	enum class State
	{
		Active,
		Paused,
		Dead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function call from Game (not overridable)
	void Update(float dtAsSeconds);
	// Updates all components attached to the actor (not overridable)
	void UpdateComponents(float dtAsSeconds);
	// Actor specific updates (overridable)
	virtual void UpdateActor(float dtAsSeconds);

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	// Getters / setters
	State GetState() const { return m_state; }
	void SetState(State state) { m_state = state; }
	class Game* GetGame() { return m_game; }

protected:
	State m_state;
	float m_position[2];
	float m_scale;
	float m_rotation;

private:
	std::vector<class Component*> m_components;
	class Game* m_game;
};
