#pragma once

#include <SFML/Graphics.hpp>    // sf::Text, sf::Font
#include "Actor.h"
#include "Color.h"

class RgbLevers : public Actor
{
public:
    RgbLevers(class Game* game);
    ~RgbLevers();
    
    void Initialize();
    void UpdateActor(float dtAsSeconds) override;
    
    bool CheckCollision(float X, float Y);
    
    // Getters / setters
    Color GetColor() const;
    void SetColor(Color newColor);
    void SetColor(int r, int g, int b);
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };
    
    class Lever* m_levers[3];
    class RectComponent* m_background;
    
//    class TextComponent* m_hexaText;
};
