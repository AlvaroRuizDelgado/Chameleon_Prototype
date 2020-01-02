#pragma once

#include "Actor.h"
#include <SFML/Graphics.hpp>

class RgbLevers : public Actor
{
public:
    RgbLevers(class Game* game);
    ~RgbLevers();
    
    void Initialize();
    void UpdateActor(float dtAsSeconds) override;
    
    // Getters / setters
    sf::Color GetColor();
    void SetColor(sf::Color newColor);
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };
    
    class Lever* m_levers[3];
    class RectComponent* m_background;
    
    // 3 text labels for each color and an extra one for the hexadecimal value
//    sf::Text m_colorsText[4];
};
