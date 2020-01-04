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
    void AdjustGradients(int changedLever);
    
    // Getters / setters
    Color GetColor() const;
    void SetColor(Color newColor);
    void SetColor(int r, int g, int b);
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };
    
    class RectComponent* m_background;
    class Lever* m_hue;
    class Lever* m_brightSat;
};