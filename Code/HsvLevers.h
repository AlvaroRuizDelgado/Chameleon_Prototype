#pragma once

#include "Actor.h"
#include "Color.h"

class HsvLevers : public Actor
{
public:
    HsvLevers(class Game* game);
    ~HsvLevers();
    
    void Initialize();
    void UpdateActor(float dtAsSeconds) override;
    
    bool CheckCollision(float X, float Y);
    //void AdjustGradients(int changedLever);
    void AdjustBrightSatBox();
    
    // Getters / setters
    Color GetColor() const;
    void SetColor(Color newColor);
    void SetColor(int r, int g, int b) { this->SetColor(Color(r, g, b)); };
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };

    float m_hue;
    float m_saturation;
    float m_brightness;
    
    class RectComponent* m_background;
    class Lever* m_hueLever;
    class Lever* m_brightSatBox;
};
