#pragma once

#include "Actor.h"
#include "Color.h"

class Background : public Actor
{
private:
	static constexpr float INITIAL_CHANGE_PER_SEC{ 0.4f };
	const int INITIAL_COLOR[3]{ 77, 133, 63 };

    Color m_bgColor;
    Color m_targetColor;
	float m_changePerSec;

    class RectComponent* m_rectComp;

private:
	void NewTargetColor();

public:
	Background(class Game* game);
    ~Background();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;
    
    // Getters / setters
	Color GetCurrentColor() const { return m_bgColor; };
	Color GetTargetColor() const { return m_targetColor; };
};
