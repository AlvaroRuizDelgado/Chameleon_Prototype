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
    
    // Getters / setters
    Color GetColor() const { return m_color; };
    void SetColor(Color newColor);
    void SetColor(int r, int g, int b) { this->SetColor(Color(r, g, b)); };
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };

    float m_hue;
    float m_saturation;
    float m_brightness;
    Color& m_color;
    
    class RectComponent* m_background;
    class Lever* m_hueLever;
    class Lever* m_brightSatBox;
};
