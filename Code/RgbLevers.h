#pragma once

#include <SFML/Graphics.hpp>    // sf::Text, sf::Font
#include "Actor.h"
#include "Color.h"

class RgbLevers : public Actor
{
public:
    RgbLevers(class Game* game, Color& color);
    ~RgbLevers();
    
    void Initialize();
    void UpdateActor(float dtAsSeconds) override;
    
    bool CheckCollision(float X, float Y);
    void AdjustGradients(int changedLever);
    void UpdateColor();
    
    // Getters / setters
    Color GetColor() const { return m_color; };
    void SetHexaTag(Color color);
    
private:
    const int INITIAL_COLOR[3] { 76, 200, 91 };
    
    class RectComponent* m_background;
    class Lever* m_levers[3];
    class TextComponent* m_hexaTag;
    Color& m_color;
};
