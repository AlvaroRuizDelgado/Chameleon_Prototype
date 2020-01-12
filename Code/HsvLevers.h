#pragma once

#include "Actor.h"
#include "Color.h"

class HsvLevers : public Actor
{
public:
    HsvLevers(class Game* game, Color& color);
    ~HsvLevers();
    
    void Initialize();
    void UpdateActor(float dtAsSeconds) override;
    
    bool CheckCollision(float X, float Y);
    void AdjustBrightSatBox();
    void UpdateColor();
    
    // Getters / setters
    Color GetColor() const { return m_color; };
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };

    Color& m_color;
    
    class RectComponent* m_background;
    class Lever* m_hueLever;
    class Lever* m_brightSatBox;
};
