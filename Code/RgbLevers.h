#pragma once

#include "Actor.h"
#include "Color.h"

class RgbLevers : public Actor
{
public:
    RgbLevers(class Game* game);
    ~RgbLevers();
    
    void Initialize();
    void UpdateActor(float dtAsSeconds) override;
    
    // Getters / setters
    Color GetColor();
    void SetColor(Color newColor);
    void SetColor(int r, int g, int b);
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };
    
    class Lever* m_levers[3];
    class RectComponent* m_background;
    
    // 3 text labels for each color and an extra one for the hexadecimal value
//    sf::Text m_colorsText[4];
};
