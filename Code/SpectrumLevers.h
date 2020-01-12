#pragma once

#include "Actor.h"
#include "Color.h"

class SpectrumLevers : public Actor
{
public:
    SpectrumLevers(class Game* game, Color& color);
	~SpectrumLevers();

    void Initialize();
    void UpdateActor(float dtAsSeconds) override;

    bool CheckCollision(float X, float Y);
    void UpdateColor();

    // Getters / setters
    Color GetColor() const { return m_color; };

private:
    const int INITIAL_COLOR[3]{ 76, 200, 91 };

    Color& m_color;

    class RectComponent* m_background;
    class Lever* m_topBox;
    class Lever* m_bottomBox;
};